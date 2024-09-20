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
