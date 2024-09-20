function createTaskElement(todo) {
    const li = document.createElement('li');
    if (todo.isCompleted) {
        li.classList.add('isCompleted');
    }

    const checkboxP = document.createElement('p');
    checkboxP.classList.add('checkbox');
    const checkbox = document.createElement('input');
    checkbox.type = 'checkbox';

    checkbox.checked = todo.isCompleted;
    checkboxP.appendChild(checkbox);

    const textP = document.createElement('p');
    textP.classList.add('text');
    textP.textContent = todo.task;

    li.appendChild(checkboxP);
    li.appendChild(textP);

    return li;
}

module.exports = {
    createTaskElement
};