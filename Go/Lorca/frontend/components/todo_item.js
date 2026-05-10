export function renderList(todos, onToggle) {
  const container = document.getElementById('list-area');
  container.innerHTML = '';
  todos.forEach((todo) => {
    const li = document.createElement('li');
    li.className = 'todo-item' + (todo.isCompleted ? ' completed' : '');

    const cb = document.createElement('input');
    cb.type = 'checkbox';
    cb.className = 'checkbox';
    cb.checked = todo.isCompleted;
    cb.addEventListener('change', async () => {
      await goToggleTodo(todo.id);
      onToggle();
    });

    const span = document.createElement('span');
    span.className = 'task-text';
    span.textContent = todo.task;

    li.appendChild(cb);
    li.appendChild(span);
    container.appendChild(li);
  });
}