pub const STYLE: &str = r#"
    /* タイトル */
    .title {
        color: #FFFFFF;
        font-size: 18px;
        font-weight: bold;
        height: auto;
        width: 1s;
        bottom: 14px;
        background-color: transparent;
    }

    /* Input フィールド */
    textbox.todo-input {
        background-color: #303030;
        border-color: transparent;
        border-width: 1px;
        corner-radius: 4px;
        color: #FFFFFF;
        font-size: 14px;
        height: 35px;
        width: 1s;
        bottom: 14px;
        child-left: 16px;
        child-right: 16px;
        child-top: 1s;
        child-bottom: 1s;
    }

    textbox.todo-input:checked,
    textbox.todo-input:focus-visible {
        border-color: #5DC2AF;
    }

    textbox.todo-input > label.placeholder {
        color: #9B9B9B;
        background-color: transparent;
        child-left: 0px;
    }

    /* タブメニュー */
    .tab-bar {
        height: auto;
        width: 1s;
        bottom: 3px;
        background-color: transparent;
        col-between: 0px;
    }

    button.tab-btn {
        height: 28px;
        background-color: transparent;
        border-width: 0px;
        corner-radius: 0px;
    }

    button.tab-btn label {
        color: #D2D2D2;
        font-size: 14px;
        background-color: transparent;
    }

    button.tab-btn.active label {
        font-weight: bold;
    }

    /* Todo リスト */
    .todo-list {
        width: 1s;
        height: auto;
        background-color: transparent;
        row-between: 5px;
    }

    .todo-item {
        background-color: #2A2A2A;
        height: 35px;
        width: 1s;
        corner-radius: 4px;
        child-left: 10px;
        child-right: 10px;
        child-top: 1s;
        child-bottom: 1s;
        col-between: 0px;
    }

    .todo-item-text {
        color: #D2D2D2;
        font-size: 14px;
        height: auto;
        width: 1s;
        background-color: transparent;
        child-top: 1s;
        child-bottom: 1s;
    }

    .todo-item-text.completed {
        color: #9B9B9B;
        text-decoration-line: strikethrough;
    }

    /* カスタム円形チェックボックス */
    .checkbox {
        width: 16px;
        height: 16px;
        min-width: 16px;
        min-height: 16px;
        corner-radius: 8px;
        border-width: 2px;
        border-color: #D9D9D9;
        background-color: transparent;
        right: 18px;
    }

    .checkbox.checked {
        background-color: #5DC2AF;
        border-color: #5DC2AF;
    }
"#;