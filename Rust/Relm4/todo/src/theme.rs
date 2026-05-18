pub const APP_CSS: &str = r#"
window {
    background-color: #1C1C1C;
}

.title-label {
    color: #FFFFFF;
    font-size: 18px;
    font-weight: bold;
}

entry.todo-input {
    background-color: #303030;
    color: #FFFFFF;
    border: 1px solid transparent;
    border-radius: 4px;
    box-shadow: none;
    outline: none;
    min-height: 35px;
    caret-color: #FFFFFF;
}

entry.todo-input > text {
    background: transparent;
}

entry.todo-input > text > placeholder {
    color: #9B9B9B;
}

entry.todo-input:focus-within {
    border-color: #5DC2AF;
}

button.tab-button {
    background: none;
    background-color: transparent;
    border: none;
    border-radius: 0;
    box-shadow: none;
    outline: none;
    color: #D2D2D2;
    font-size: 14px;
    min-height: 28px;
    padding-left: 8px;
    padding-right: 8px;
    padding-top: 0;
    padding-bottom: 0;
}

button.tab-button:hover,
button.tab-button:active {
    background: none;
    background-color: transparent;
    box-shadow: none;
}

button.tab-button-active {
    font-weight: bold;
}

.todo-item-box {
    background-color: #2A2A2A;
    border-radius: 4px;
    min-height: 35px;
    padding: 2px 10px;
}

.todo-text {
    color: #D2D2D2;
    font-size: 14px;
}

.todo-text-completed {
    color: #9B9B9B;
    text-decoration: line-through;
}

checkbutton.todo-checkbox {
    min-width: 16px;
    min-height: 16px;
    margin-right: 18px;
}

checkbutton.todo-checkbox check {
    border-radius: 50%;
    min-width: 16px;
    min-height: 16px;
    border: 2px solid #D9D9D9;
    background-color: transparent;
    background-image: none;
    -gtk-icon-size: 12px;
}

checkbutton.todo-checkbox:checked check {
    border-color: #D9D9D9;
    background-color: transparent;
    background-image: none;
    color: #5DC2AF;
}
"#;
