import 'package:flutter/material.dart';

void main() {
  runApp(ToDo());
}

class ToDo extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'ToDo APP',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: TodoListPage(),
    );
  }
}

class CheckBoxListTileModel {
  String title;
  bool isCheck;

  CheckBoxListTileModel({this.title, this.isCheck});
}

class MenuListModel {
  String title;
  bool isActive;
  double width;

  MenuListModel({this.title, this.isActive, this.width});
}

class TodoListPage extends StatefulWidget {
  @override
  _TodoListPageState createState() => _TodoListPageState();
}

class _TodoListPageState extends State<TodoListPage> {
  List<CheckBoxListTileModel> todoList = [
    CheckBoxListTileModel(title: "Task 1", isCheck: true),
    CheckBoxListTileModel(title: "Task 2", isCheck: false),
    CheckBoxListTileModel(title: "Task 3", isCheck: false),
    CheckBoxListTileModel(title: "Task 4", isCheck: true),
  ];

  List<CheckBoxListTileModel> _foundTodoList = [];
  String _menu;

  @override
  initState() {
    _foundTodoList = todoList;
    _menu = "All";
    super.initState();
  }

  List<MenuListModel> menuList = [
    MenuListModel(title: "All", isActive: true, width: 30),
    MenuListModel(title: "Active", isActive: false, width: 50),
    MenuListModel(title: "Completed", isActive: false, width: 80),
  ];

  final TextEditingController _textFormController =
      new TextEditingController(text: '');

  List<CheckBoxListTileModel> filterDisplayTodoList(type) {
    if (type == "Active") return todoList.where((i) => !i.isCheck).toList();
    if (type == "Completed") return todoList.where((i) => i.isCheck).toList();
    return todoList;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color.fromRGBO(28, 28, 28, 1),
      body: Container(
        padding: EdgeInsets.only(top: 10, left: 24, right: 24),
        child: Container(
            child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: <Widget>[
              Text("ToDo",
                  style: TextStyle(
                      color: Colors.white,
                      fontWeight: FontWeight.bold,
                      fontSize: 18)),
              const SizedBox(height: 12),
              TextFormField(
                  controller: _textFormController,
                  style: TextStyle(
                    color: Colors.white,
                  ),
                  decoration: InputDecoration(
                    hintText: 'Add Task',
                    hintStyle: TextStyle(
                        fontSize: 14.0,
                        color: Color.fromRGBO(155, 155, 155, 1)),
                    filled: true,
                    fillColor: Color.fromRGBO(48, 48, 48, 1),
                    enabledBorder: OutlineInputBorder(
                      borderRadius: BorderRadius.circular(8),
                    ),
                    focusedBorder: OutlineInputBorder(
                      borderRadius: BorderRadius.circular(8),
                    ),
                  ),
                  onFieldSubmitted: (String value) {
                    if (!value.isEmpty) {
                      setState(() {
                        todoList.add(
                          CheckBoxListTileModel(title: value, isCheck: false),
                        );
                        _foundTodoList = filterDisplayTodoList(_menu);
                      });
                      _textFormController.clear();
                    }
                  }),
              const SizedBox(height: 12),
              Row(
                children: [
                  for (final menu in menuList)
                    MouseRegion(
                      cursor: SystemMouseCursors.click,
                      child: GestureDetector(
                        onTap: () {
                          setState(() {
                            resetMenuActive();
                            menu.isActive = true;
                            _menu = menu.title;
                            _foundTodoList = filterDisplayTodoList(_menu);
                          });
                        },
                        child: Card(
                          color: Colors.transparent,
                          elevation: 0,
                          child: Container(
                            child: Text(
                              menu.title,
                              style: TextStyle(
                                fontSize: 14,
                                fontWeight: menu.isActive
                                    ? FontWeight.bold
                                    : FontWeight.normal,
                                color: Color.fromRGBO(210, 210, 210, 1),
                              ),
                            ),
                            height: 20,
                            width: menu.width,
                          ),
                        ),
                      ),
                    ),
                ],
              ),
              Expanded(
                child: ListView.builder(
                  itemCount: _foundTodoList.length,
                  itemBuilder: (BuildContext context, int index) {
                    return Card(
                        color: Color.fromRGBO(42, 42, 42, 1),
                        elevation: 0,
                        child: Theme(
                          data: ThemeData(
                            unselectedWidgetColor:
                                Color.fromRGBO(217, 217, 217, 1),
                          ),
                          child: CheckboxListTile(
                            value: _foundTodoList[index].isCheck,
                            controlAffinity: ListTileControlAffinity.leading,
                            title: Text(_foundTodoList[index].title,
                                style: TextStyle(
                                  color: Color.fromRGBO(210, 210, 210, 1),
                                  decorationThickness: 2,
                                  decoration: _foundTodoList[index].isCheck
                                      ? TextDecoration.lineThrough
                                      : TextDecoration.none,
                                )),
                            onChanged: (value) {
                              setState(() {
                                _foundTodoList[index].isCheck = value;
                                _foundTodoList = filterDisplayTodoList(_menu);
                              });
                            },
                          ),
                        ));
                  },
                ),
              ),
            ])),
      ),
    );
  }

  void resetMenuActive() {
    for (final menu in menuList) menu.isActive = false;
  }
}
