const { initTodoApp } = require('./src/js/AppController.js');

document.addEventListener('DOMContentLoaded', () => {
    const todoApp = initTodoApp([
        { task: 'Task1' },
        { task: 'Task2', isCompleted: true },
        { task: 'Task3' },
        { task: 'Task4' }
    ]);
});
