export function initInput(onAdd) {
  document.getElementById('todo-input').addEventListener('keydown', async (e) => {
    if (e.key !== 'Enter') return;
    const input = e.target;
    const task = input.value.trim();
    if (!task) return;
    await goAddTodo(task);
    input.value = '';
    onAdd();
  });
}