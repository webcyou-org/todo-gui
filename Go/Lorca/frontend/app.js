import { initInput } from './components/input.js';
import { renderTabs } from './components/tabs.js';
import { renderList } from './components/todo_item.js';

async function render() {
  const todos = await goGetTodos();
  const tabs  = await goGetTabs();
  renderTabs(tabs, render);
  renderList(todos, render);
}

initInput(render);
render();