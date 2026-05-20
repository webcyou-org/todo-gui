use egui::{FontId, RichText, Sense, Stroke};

use crate::data::{TabFilter, Todo};
use crate::theme::*;

#[cfg(target_os = "macos")]
extern "C" {
    fn activate_ime();
}

#[derive(serde::Deserialize, serde::Serialize)]
#[serde(default)]
pub struct ToDoApp {
    todos: Vec<Todo>,
    next_id: usize,
    active_tab: TabFilter,
    #[serde(skip)]
    input_text: String,
}

impl Default for ToDoApp {
    fn default() -> Self {
        let mut app = Self {
            todos: Vec::new(),
            next_id: 1,
            active_tab: TabFilter::default(),
            input_text: String::new(),
        };
        app.add_todo("Task 1".into());
        app.todos.push(Todo { id: app.next_id, task: "Task 2".into(), is_completed: true });
        app.next_id += 1;
        app.add_todo("Task 3".into());
        app.add_todo("Task 4".into());
        app
    }
}

impl ToDoApp {
    pub fn new(cc: &eframe::CreationContext<'_>) -> Self {
        Self::apply_theme(&cc.egui_ctx);
        #[cfg(target_os = "macos")]
        unsafe { activate_ime() };
        if let Some(storage) = cc.storage {
            return eframe::get_value(storage, eframe::APP_KEY).unwrap_or_default();
        }
        Default::default()
    }

    fn apply_theme(ctx: &egui::Context) {
        let mut v = egui::Visuals::dark();
        v.panel_fill = C_BG;
        v.window_fill = C_BG;
        v.extreme_bg_color = C_INPUT;
        v.selection.bg_fill = C_ACCENT.linear_multiply(0.4);
        v.widgets.noninteractive.fg_stroke = Stroke::new(1.0, C_TEXT);
        v.widgets.inactive.fg_stroke = Stroke::new(1.0, C_TEXT);
        v.widgets.hovered.fg_stroke = Stroke::new(1.0, C_WHITE);
        v.widgets.active.fg_stroke = Stroke::new(1.0, C_WHITE);
        v.widgets.noninteractive.bg_fill = C_BG;
        v.widgets.inactive.bg_fill = C_BG;
        v.widgets.hovered.bg_fill = C_SURFACE;
        ctx.set_visuals(v);

        let mut fonts = egui::FontDefinitions::default();

        // Inter: primary proportional font
        fonts.font_data.insert(
            "inter".to_owned(),
            egui::FontData::from_static(include_bytes!("../assets/Inter-Regular.ttf")),
        );
        // Inter Bold: for bold/heading text
        fonts.font_data.insert(
            "inter_bold".to_owned(),
            egui::FontData::from_static(include_bytes!("../assets/Inter-Bold.ttf")),
        );
        // NotoSansJP: Japanese glyph fallback
        fonts.font_data.insert(
            "noto_sans_jp".to_owned(),
            egui::FontData::from_static(include_bytes!("../assets/NotoSansJP-Regular.ttf")),
        );

        // Proportional: Inter Regular → NotoSansJP (fallback for CJK)
        let prop = fonts.families.entry(egui::FontFamily::Proportional).or_default();
        prop.insert(0, "inter".to_owned());
        prop.push("noto_sans_jp".to_owned());

        // Named "bold" family: Inter Bold → NotoSansJP (used for strong/heading text)
        fonts.families.insert(
            egui::FontFamily::Name("bold".into()),
            vec!["inter_bold".to_owned(), "noto_sans_jp".to_owned()],
        );

        ctx.set_fonts(fonts);

        // Map bold text styles to Inter Bold
        ctx.style_mut(|s| {
            use egui::{FontFamily, TextStyle};
            let bold = FontFamily::Name("bold".into());
            s.text_styles.insert(TextStyle::Heading,   FontId::new(18.0, bold.clone()));
            s.text_styles.insert(TextStyle::Body,      FontId::new(14.0, FontFamily::Proportional));
            s.text_styles.insert(TextStyle::Button,    FontId::new(14.0, bold.clone()));
            s.text_styles.insert(TextStyle::Small,     FontId::new(11.0, FontFamily::Proportional));
            s.text_styles.insert(TextStyle::Monospace, FontId::new(14.0, FontFamily::Monospace));
        });
    }

    fn add_todo(&mut self, task: String) {
        self.todos.push(Todo { id: self.next_id, task, is_completed: false });
        self.next_id += 1;
    }

    // ── Title ──────────────────────────────────────────────────────────────

    fn show_title(&self, ui: &mut egui::Ui) {
        ui.label(
            RichText::new("ToDo")
                .font(FontId::new(18.0, egui::FontFamily::Name("bold".into())))
                .color(C_WHITE),
        );
    }

    // ── Input ──────────────────────────────────────────────────────────────

    fn show_input(&mut self, ui: &mut egui::Ui) {
        let available_w = ui.available_width();

        // Allocate fixed 35px row; paint custom background manually
        let (bg_rect, _) = ui.allocate_exact_size(
            egui::vec2(available_w, 35.0),
            Sense::hover(),
        );
        ui.painter().rect_filled(bg_rect, 4.0, C_INPUT);

        // Vertically center the TextEdit within the 35px row.
        // Inter has taller ascenders than egui's default font, so compute the
        // center explicitly rather than using a fixed symmetric shrink.
        let text_h = 22.0; // room for Inter 14pt including ascender/descender
        let top    = bg_rect.min.y + (bg_rect.height() - text_h) / 2.0;
        let inner_rect = egui::Rect::from_min_max(
            egui::pos2(bg_rect.min.x + 16.0, top),
            egui::pos2(bg_rect.max.x - 16.0, top + text_h),
        );
        let input_response = ui.put(
            inner_rect,
            egui::TextEdit::singleline(&mut self.input_text)
                .frame(false)
                .hint_text(RichText::new("Add Task").color(C_MUTED))
                .font(FontId::proportional(14.0))
                .text_color(C_WHITE)
                .desired_width(f32::INFINITY),
        );

        // Focus border
        if input_response.has_focus() {
            ui.painter()
                .rect_stroke(bg_rect, 4.0, Stroke::new(1.0, C_ACCENT));
        }

        // Submit on Enter, but not when IME just committed text (its Enter must not submit the form).
        let just_committed_ime = ui.input(|i| {
            i.events.iter().any(|e| matches!(e, egui::Event::Ime(egui::ImeEvent::Commit(_))))
        });
        if input_response.lost_focus()
            && ui.input(|i| i.key_pressed(egui::Key::Enter))
            && !just_committed_ime
        {
            let task = self.input_text.trim().to_string();
            if !task.is_empty() {
                self.add_todo(task);
                self.input_text.clear();
            }
        }
    }

    // ── Tabs ───────────────────────────────────────────────────────────────

    fn show_tabs(&mut self, ui: &mut egui::Ui) {
        ui.horizontal(|ui| {
            ui.set_min_height(28.0);
            ui.spacing_mut().item_spacing.x = 0.0;

            for tab in TabFilter::all() {
                ui.add_space(8.0);
                let text = if self.active_tab == tab {
                    RichText::new(tab.label())
                        .font(FontId::new(14.0, egui::FontFamily::Name("bold".into())))
                        .color(C_TEXT)
                } else {
                    RichText::new(tab.label()).size(14.0).color(C_TEXT)
                };
                if ui
                    .add(egui::Label::new(text).sense(Sense::click()))
                    .clicked()
                {
                    self.active_tab = tab;
                }
                ui.add_space(8.0);
            }
        });
    }

    // ── Todo list ──────────────────────────────────────────────────────────

    fn show_list(&mut self, ui: &mut egui::Ui) {
        let filtered_ids: Vec<usize> = self
            .todos
            .iter()
            .filter(|t| self.active_tab.matches(t))
            .map(|t| t.id)
            .collect();

        let mut toggle_id: Option<usize> = None;

        egui::ScrollArea::vertical()
            .auto_shrink([false, false])
            .show(ui, |ui| {
                let available_w = ui.available_width();
                ui.spacing_mut().item_spacing.y = 5.0;

                for &id in &filtered_ids {
                    let (task, is_completed) = {
                        let t = self.todos.iter().find(|t| t.id == id).unwrap();
                        (t.task.clone(), t.is_completed)
                    };

                    let (rect, response) = ui.allocate_exact_size(
                        egui::vec2(available_w, 35.0),
                        Sense::click(),
                    );

                    if ui.is_rect_visible(rect) {
                        paint_todo_row(ui.painter(), rect, &task, is_completed);
                    }

                    if response.clicked() {
                        toggle_id = Some(id);
                    }
                }
            });

        if let Some(id) = toggle_id {
            if let Some(t) = self.todos.iter_mut().find(|t| t.id == id) {
                t.is_completed = !t.is_completed;
            }
        }
    }
}

// ── Custom todo row painter ────────────────────────────────────────────────

fn paint_todo_row(
    painter: &egui::Painter,
    rect: egui::Rect,
    task: &str,
    is_completed: bool,
) {
    // Background
    painter.rect_filled(rect, 4.0, C_SURFACE);

    // Checkbox: center at (rect.min.x + padL + radius, rect.center.y)
    let cb_radius = 8.0_f32;
    let cb_center = egui::pos2(rect.min.x + 10.0 + cb_radius, rect.center().y);

    if is_completed {
        painter.circle_stroke(cb_center, cb_radius - 0.75, Stroke::new(1.5, C_CB_BORDER));
        let stroke = Stroke::new(1.5, C_ACCENT);
        // Checkmark proportions matching Fyne/Kivy implementations
        painter.line_segment(
            [
                egui::pos2(cb_center.x - 4.0, cb_center.y),
                egui::pos2(cb_center.x - 1.0, cb_center.y + 3.0),
            ],
            stroke,
        );
        painter.line_segment(
            [
                egui::pos2(cb_center.x - 1.0, cb_center.y + 3.0),
                egui::pos2(cb_center.x + 4.0, cb_center.y - 3.0),
            ],
            stroke,
        );
    } else {
        // Stroke radius is inset by half stroke-width so outer edge = cb_radius
        painter.circle_stroke(
            cb_center,
            cb_radius - 0.75,
            Stroke::new(1.5, C_CB_BORDER),
        );
    }

    // Label: padL(10) + cbSize(16) + cbMarginRight(18) = 44
    let text_x = rect.min.x + 44.0;
    let font_id = FontId::proportional(14.0);
    let text_color = if is_completed { C_MUTED } else { C_TEXT };

    if is_completed {
        // Layout text to measure width for strikethrough line
        let galley = painter
            .ctx()
            .fonts(|f| f.layout_no_wrap(task.to_string(), font_id, text_color));
        let text_w = galley.size().x;
        let text_top = rect.center().y - galley.size().y / 2.0;
        painter.galley(egui::pos2(text_x, text_top), galley, text_color);
        // Strikethrough
        painter.line_segment(
            [
                egui::pos2(text_x, rect.center().y),
                egui::pos2(text_x + text_w, rect.center().y),
            ],
            Stroke::new(1.0, C_MUTED),
        );
    } else {
        painter.text(
            egui::pos2(text_x, rect.center().y),
            egui::Align2::LEFT_CENTER,
            task,
            font_id,
            text_color,
        );
    }
}

// ── eframe::App ────────────────────────────────────────────────────────────

impl eframe::App for ToDoApp {
    fn save(&mut self, storage: &mut dyn eframe::Storage) {
        eframe::set_value(storage, eframe::APP_KEY, self);
    }

    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default()
            .frame(egui::Frame::none().fill(C_BG))
            .show(ctx, |ui| {
                egui::Frame::none()
                    .inner_margin(egui::Margin {
                        left: 24.0,
                        right: 24.0,
                        top: 10.0,
                        bottom: 10.0,
                    })
                    .show(ui, |ui| {
                        self.show_title(ui);
                        ui.add_space(14.0);
                        self.show_input(ui);
                        ui.add_space(14.0);
                        self.show_tabs(ui);
                        ui.add_space(3.0);
                        self.show_list(ui);
                    });
            });
    }
}