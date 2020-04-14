# Learning Javascript

Notes taken from [this](https://javabrains.io/courses/corejs_objectsprototypes/) course

- **Creating an object** in JS can be done using the a function:

```javascript

function createEmployee(name, role) {
	var obj = {};
	obj.name = name;
	obj.role = role;
	return obj;
}

var emp1 = createEmployee("tintin", "CTO");

```

- **Creating an object** in JS can be done using the `new` keyword:

```javascript

function Employee(name, role) {
	this.name = name;
	this.role = role;
}

var emp2 = new Employee("tintin", "CTO");

```

- Its the fact to use the `new` keyword that makes the function behave as a constructor
- When using the `new` keyword, the interpreter initializes an empty object at the beginning of 
the constructor function and returns it at the end. 

- There are 4 ways to call function in JS: 
	- Method 1
	```js 
	function func() {
		console.log('Hello');
	}
	func();
	```
	- Method 2
	```js
	var obj = {};
	obj.func = function () {
		console.log('Hello');
	};
	obj.foo();
	```
	- Method 3: Using the `new` keyword
	- Method 4: Using the `call(instance)` property 
	```js
	var obj = new Obj();
	obj.foo.call();
	```


	- In the body of a function, we can access 2 objects: `arguments` and `this`. Depending on the function method, the `this` takes different value: 
		- Method 1, `this` takes the global object (The `window` in the case where JS is ran in a browser), which makes sense since when declaring functions and variables in the global scope they get added as properties of the global object
		- Method 2, `this` is refering to the object instance 
		- Method 3, `this` is refering to the object under construction
		- Method 4, `this` is refering to the instance being passed to the call function as an argument

- When writing a constructor function, the `this` may refer to different object:
```js
function Employee(name, role) {
	this.name = name;  // Refers to the object being created
	this.role = role;  // Refers to the object being created
	this.getPromotion = function() {
		this.role = "CEO"; // Refers to the object on which the 
		                   // getPromotion method is being called
	}
}
```

- Every function in JS has a property named `call` which call the function. 
It takes an argument to which the `this` will refer to.
```js
function Bicycle () {
	this.tirePressure = 10.;
	this.inflate = function () {
		this.tirePressure += 3;
	}
}

function Mechanic (name) {
	this.name = name;
}

bic = new Bicycle();
mike = new Mechanic('mike');
mike.inflate = bic.inflate;

mike.inflate(); // This will try to inflate the tirePressure of 
                // mike (which does not exist)
mike.inflate.call(bic);  // This will inflate the tirePressure of 
                         // the instance being passed to the call function

```

- JS is not a `class based` object oriented language
- In JS objects don't own methods, they have properties, some of which happen to be function. Several instances of the same 'object' will have their own copy of the properties
- Every time a function is declared, the interpreter creates two objects: 
	- the function object
	- the prototype object
The function object has a property is the correspond prototype instance: 
```js
function greet () { 
	console.log('Hello');
}
foo.prototype;
```
- When accessing to the property of an instance, the interpreter performs some steps: 
  1. It checks if the instance has the property, and if it has, it returns it
  2. If it has not, it checks if the prototype object has this property. If it has, it returns it. If not, undefined is returned