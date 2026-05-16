namespace TodoApp;

public static class Theme
{
    public const string C_BG        = "#1C1C1C";
    public const string C_SURFACE   = "#2A2A2A";
    public const string C_INPUT     = "#303030";
    public const string C_TEXT      = "#D2D2D2";
    public const string C_WHITE     = "#FFFFFF";
    public const string C_MUTED     = "#9B9B9B";
    public const string C_ACCENT    = "#5DC2AF";
    public const string C_CB_BORDER = "#D9D9D9";

    public const string Css = """
        window, * {
            background-color: #1C1C1C;
            color: #D2D2D2;
            font-size: 14px;
        }
        .title-label {
            color: #FFFFFF;
            font-size: 18px;
            font-weight: bold;
        }
        /* Entry: remove GTK's internal min-height; height is driven by HeightRequest in code */
        .todo-input {
            background-color: #303030;
            color: #FFFFFF;
            border-radius: 4px;
            border: 1px solid transparent;
            padding: 4px 16px;
            min-height: 0;
        }
        .todo-input:focus {
            border-color: #5DC2AF;
        }
        .tab-btn {
            background: transparent;
            border: none;
            color: #D2D2D2;
            font-size: 14px;
            padding: 0 8px;
            min-height: 0;
            box-shadow: none;
        }
        .tab-btn:hover {
            background: transparent;
        }
        .tab-btn.active {
            font-weight: bold;
        }
        /* Todo row: padding drives vertical centering; HeightRequest=35 set in code */
        .todo-item {
            background-color: #2A2A2A;
            border-radius: 4px;
            padding: 0 10px;
            min-height: 0;
        }
        /* Children inside a todo-item must be transparent to show #2A2A2A */
        .todo-item * {
            background-color: transparent;
        }
        .todo-item-text {
            color: #D2D2D2;
            font-size: 14px;
        }
        .todo-item-text.completed {
            color: #9B9B9B;
            text-decoration: line-through;
        }
        /* Checkbox: zero out GTK button defaults; size enforced by SizeRequest in code */
        .checkbox-circle {
            background: transparent;
            border: 2px solid #D9D9D9;
            border-radius: 8px;
            min-width: 0;
            min-height: 0;
            padding: 0;
            box-shadow: none;
        }
        .checkbox-circle:hover {
            background-color: transparent;
        }
        /* Use !important so .todo-item * transparent doesn't win */
        .checkbox-circle.checked,
        .todo-item .checkbox-circle.checked {
            background-color: #5DC2AF;
            border-color: #5DC2AF;
        }
        scrolledwindow, viewport {
            background-color: #1C1C1C;
        }
        """;
}