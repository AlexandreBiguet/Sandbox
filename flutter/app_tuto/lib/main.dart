// Construted following this tuto:
//  https://www.youtube.com/watch?v=GLSG_Wh_YWc

import 'package:flutter/material.dart';

import './product_manager.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      theme: ThemeData(
          brightness: Brightness.light,
          primarySwatch: Colors.deepOrange,
          accentColor: Colors.deepPurple),
      home: Scaffold(
        appBar: AppBar(
          title: Text('Easy List Test'),
        ),
        body: ProductManager(startingProduct: 'A First element'),
      ),
    );
  }
}
