use leptos::*;
use crate::data::TabFilter;

#[component]
pub fn TabMenu(active_tab: RwSignal<TabFilter>) -> impl IntoView {
    view! {
        <div class="tab-menu">
            {[TabFilter::All, TabFilter::Active, TabFilter::Completed]
                .into_iter()
                .map(|tab| view! {
                    <button
                        class=move || if active_tab.get() == tab { "tab-btn active" } else { "tab-btn" }
                        on:click=move |_| active_tab.set(tab)
                    >
                        {tab.label()}
                    </button>
                })
                .collect_view()
            }
        </div>
    }
}