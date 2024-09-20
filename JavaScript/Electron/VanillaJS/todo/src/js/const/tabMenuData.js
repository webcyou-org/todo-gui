const TAB_MENU_TEXT = {
    ALL: 'All',
    ACTIVE: 'Active',
    COMPLETED: 'Completed',
}

const tabMenuData = [
    { text: TAB_MENU_TEXT.ALL, isActive: true },
    { text: TAB_MENU_TEXT.ACTIVE, isActive: false },
    { text: TAB_MENU_TEXT.COMPLETED, isActive: false }
]

module.exports = {
    tabMenuData,
    TAB_MENU_TEXT
};
