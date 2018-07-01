// use std::io;

fn main() {

    println!("In main function");

    function1();

    function2(4.0, 12.0);

    let f3 : f64 = function3();

    println!("result of function3 call : {}", f3);
    
}

/// Function3 : double(void)
fn function3() -> f64{
    12.0 + 4.0
}

/// Function2 : void(double, double)
fn function2(x: f64, y:f64) {
    let p = x + y;
    println!("In function2");
    println!("{} + {} = {}", x, y, p);
}

/// Function 1 : void(void)
fn function1 () {
    println!("In function1 : Hi there");
}
