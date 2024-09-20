function createMenuItem(tab) {
    const li = document.createElement('li');

    if (tab.isActive) {
        li.classList.add('isActive');
    }

    const p = document.createElement('p');
    const a = document.createElement('a');
    a.href = '#';
    a.textContent = tab.text;

    p.appendChild(a);
    li.appendChild(p);

    return li;
}

module.exports = {
    createMenuItem
};
