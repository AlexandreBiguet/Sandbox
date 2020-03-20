import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart';

import './products.dart';

class ProductManager extends StatefulWidget {
  final String startingProduct;

  ProductManager({this.startingProduct = 'Sweets Tester'}) {
    debugPrint('[ProductManager] constructor');
  }

  @override
  State<StatefulWidget> createState() {
    debugPrint('[ProductManager] createState()');
    return _ProductManagerState();
  }
}

class _ProductManagerState extends State<ProductManager> {
  List<String> _products = [];

  @override
  void initState() {
    debugPrint('[ProductManager] initState()');
    _products.add(widget.startingProduct);
    super.initState();
  }

  @override
  void didUpdateWidget(ProductManager oldWidget) {
    debugPrint('[ProductManager] didUpdateWidget()');
    super.didUpdateWidget(oldWidget);
  }

  @override
  Widget build(BuildContext context) {
    debugPrint('[ProductManager] build()');
    return Column(
      children: [
        Container(
          margin: EdgeInsets.all(10.0),
          child: RaisedButton(
            color: Theme.of(context).primaryColorLight,
            child: Text('Add a product'),
            onPressed: () {
              setState(() {
                _products.add('hard coded element');
                print(_products);
              });
            },
          ),
        ),
        Products(_products)
      ],
    );
  }
}
