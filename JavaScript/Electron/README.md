## Todo GUI in Electron

![todo](https://user-images.githubusercontent.com/1584153/191999399-373be546-9667-4e0b-92c1-c644bd7ff922.png)

### Contents

- [VanillaJS](VanillaJS)
- [Vue](Vue)
- [React](React)

### Template HTML

```html
<h1>ToDo</h1>
<p class="input todo"><input id="todoInput" type="text" placeholder="Add Task" /></p>

<ul class="list menu" id="menuList">
    <li class="isActive">
        <p>
            <a href="#">All</a>
        </p>
    </li>
    <li>
        <p>
            <a href="#">Active</a>
        </p>
    </li>
    <li>
        <p>
            <a href="#">Completed</a>
        </p>
    </li>
</ul>
<div>
    <ul class="list task" id="todoList">
        <li>
            <p class="checkbox"><input type="checkbox"></p>
            <p class="text">Task1</p>
        </li>
        <li class="isCompleted">
            <p class="checkbox"><input type="checkbox" checked></p>
            <p class="text">Task2</p>
        </li>
        <li>
            <p class="checkbox"><input type="checkbox"></p>
            <p class="text">Task3</p>
        </li>
        <li>
            <p class="checkbox"><input type="checkbox"></p>
            <p class="text">Task4</p>
        </li>
    </ul>
</div>
```

### Template CSS

```css
/* Input Style */
input {
    border: 1px solid transparent;
}

input:focus {
    outline: none;
    border: 1px solid #5DC2AF;
}

.input.todo {
    margin-bottom: 14px;
}

.input.todo input {
    width: 100%;
    min-width: 430px;
    height: 35px;
    padding: 4px 16px;
    background: #303030;
    border-radius: 4px;
    color: #FFFFFF;
}

/* Menu List Style */
.list.menu {
    display: flex;
    list-style: none;
    margin-bottom: 3px;
}

.list.menu > li {
    height: 28px;
    padding: 0 8px;
    font-size: 14px;
    line-height: 28px;
    align-items: center;
    justify-content: center;
}

.list.menu > li.isActive {
    font-weight: bold;
}

.list.menu a {
    color: #D2D2D2;
    text-decoration: none;
}

/* Task List Style */
.list.task {
    list-style: none;
}

.list.task > li {
    display: flex;
    width: 100%;
    min-width: 430px;
    height: 35px;
    padding: 10px;
    margin-bottom: 5px;
    border-radius: 4px;
    background: #2A2A2A;
    align-items: center;
    cursor: pointer;
}

.list.task > li .checkbox {
    height: 20px;
    margin-right: 18px;
}

.list.task > li .checkbox input {
    position: relative;
    appearance: none;
    width: 16px;
    height: 16px;
    border-radius: 8px;
    border: 2px solid #D9D9D9;
}

.list.task > li .checkbox input:checked::before {
    content: "";
    position: absolute;
    left: 3px;
    top: 1px;
    display: block;
    width: 4px;
    height: 6px;
    border: 2px solid #5DC2AF;
    border-top: transparent;
    border-left: transparent;
    transform: rotate(45deg);
}

.list.task > li .text {
    font-size: 14px;
    color: #D2D2D2;
    line-height: 20px;
}

.list.task > li.isCompleted .text {
    text-decoration: line-through;
}
```