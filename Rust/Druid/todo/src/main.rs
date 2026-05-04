use druid::im::Vector;
use druid::widget::{Controller, CrossAxisAlignment, Flex, Label, Padding, TextBox};
use druid::{
    AppLauncher, Color, Data, Env, Event, EventCtx, FontDescriptor, FontFamily, FontWeight,
    KbKey, Lens, Widget, WidgetExt, WindowDesc, theme,
};

// ---------------------------------------------------------------------------
// Design tokens
// ---------------------------------------------------------------------------

const BG: Color        = Color::rgb8(0x1C, 0x1C, 0x1C);
const INPUT_BG: Color  = Color::rgb8(0x30, 0x30, 0x30);
const ACCENT: Color    = Color::rgb8(0x5D, 0xC2, 0xAF);
const TEXT_WHITE: Color = Color::rgb8(0xFF, 0xFF, 0xFF);
const TEXT_MAIN: Color  = Color::rgb8(0xD2, 0xD2, 0xD2);
const TEXT_HINT: Color  = Color::rgb8(0x9B, 0x9B, 0x9B);

// ---------------------------------------------------------------------------
// Data Model
// ---------------------------------------------------------------------------

#[derive(Clone, Data, Lens, PartialEq)]
struct Todo {
    id: u64,
    task: String,
    is_completed: bool,
}

impl Todo {
    fn new(id: u64, task: impl Into<String>) -> Self {
        Self { id, task: task.into(), is_completed: false }
    }
}

#[derive(Clone, Data, PartialEq)]
enum TabFilter {
    All,
    Active,
    Completed,
}

impl TabFilter {
    fn matches(&self, todo: &Todo) -> bool {
        match self {
            TabFilter::All => true,
            TabFilter::Active => !todo.is_completed,
            TabFilter::Completed => todo.is_completed,
        }
    }
}

#[derive(Clone, Data, Lens)]
struct AppState {
    todos: Vector<Todo>,
    input: String,
    active_tab: TabFilter,
    next_id: u64,
}

impl AppState {
    fn new() -> Self {
        let todos = Vector::from(vec![
            Todo::new(1, "Task 1"),
            { let mut t = Todo::new(2, "Task 2"); t.is_completed = true; t },
            Todo::new(3, "Task 3"),
            Todo::new(4, "Task 4"),
        ]);
        Self { todos, input: String::new(), active_tab: TabFilter::All, next_id: 5 }
    }

    fn add_todo(&mut self) {
        let task = self.input.trim().to_string();
        if !task.is_empty() {
            self.todos.push_back(Todo::new(self.next_id, task));
            self.next_id += 1;
            self.input.clear();
        }
    }

    fn toggle_completed(&mut self, id: u64) {
        for todo in self.todos.iter_mut() {
            if todo.id == id {
                todo.is_completed = !todo.is_completed;
                break;
            }
        }
    }

    fn filtered_todos(&self) -> Vector<Todo> {
        self.todos.iter().filter(|t| self.active_tab.matches(t)).cloned().collect()
    }
}

// ---------------------------------------------------------------------------
// Controller: Enter キーで add_todo を呼ぶ
// ---------------------------------------------------------------------------

struct InputController;

impl<W: Widget<AppState>> Controller<AppState, W> for InputController {
    fn event(
        &mut self,
        child: &mut W,
        ctx: &mut EventCtx,
        event: &Event,
        data: &mut AppState,
        env: &Env,
    ) {
        if let Event::KeyDown(key_event) = event {
            if key_event.key == KbKey::Enter {
                data.add_todo();
                ctx.set_handled();
                return;
            }
        }
        child.event(ctx, event, data, env);
    }
}

// ---------------------------------------------------------------------------
// Input widget
// ---------------------------------------------------------------------------

fn build_input() -> impl Widget<AppState> {
    TextBox::new()
        .with_placeholder("Add Task")
        .lens(AppState::input)
        .controller(InputController)
        .fix_height(35.0)
        .expand_width()
        .env_scope(|env, _: &AppState| {
            env.set(theme::BACKGROUND_LIGHT,      INPUT_BG);
            env.set(theme::BORDER_DARK,           Color::TRANSPARENT);
            env.set(theme::PRIMARY_LIGHT,         ACCENT);
            env.set(theme::TEXT_COLOR,            TEXT_WHITE);
            env.set(theme::PLACEHOLDER_COLOR,     TEXT_HINT);
            env.set(theme::TEXTBOX_BORDER_RADIUS, 4.0_f64);
        })
}

// ---------------------------------------------------------------------------
// UI root
// ---------------------------------------------------------------------------

fn build_ui() -> impl Widget<AppState> {
    let title_font = FontDescriptor::new(FontFamily::SYSTEM_UI)
        .with_weight(FontWeight::BOLD)
        .with_size(18.0);

    let title = Label::new("ToDo")
        .with_font(title_font)
        .with_text_color(TEXT_WHITE);

    // placeholders — replaced in later steps
    let tab_placeholder  = Label::new("[Tabs]").with_text_color(TEXT_MAIN);
    let list_placeholder = Label::new("[Todo List]").with_text_color(TEXT_MAIN);

    let column = Flex::column()
        .cross_axis_alignment(CrossAxisAlignment::Start)
        .with_child(title)
        .with_spacer(14.0)
        .with_child(build_input())
        .with_spacer(14.0)
        .with_child(tab_placeholder)
        .with_spacer(3.0)
        .with_flex_child(list_placeholder, 1.0);

    Padding::new((24.0, 10.0), column)
        .background(BG)
        .expand()
}

fn main() {
    let main_window = WindowDesc::new(build_ui())
        .window_size((800.0, 600.0))
        .title("ToDo");

    AppLauncher::with_window(main_window)
        .launch(AppState::new())
        .expect("Failed to launch application");
}