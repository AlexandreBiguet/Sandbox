import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart';

class Products extends StatelessWidget {
  final List<String> _products;

  Products([this._products = const []]) {
    debugPrint('Products Widget] constructor');
  }

  @override
  Widget build(BuildContext context) {
    debugPrint('[Products Widget] build()');
    return Column(
      children: _products
          .map((element) => Card(
                child: Column(
                  children: <Widget>[
                    Image.asset('assets/croissant.jpg'),
                    Text(element),
                  ],
                ),
              ))
          .toList(),
    );
  }
}
