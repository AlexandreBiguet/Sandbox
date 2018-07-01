use std::io;

/// Is that how doc works ? Nope

fn main() {
    println!("Guess the number!");

    println!("Please input your guess.");

    // Default : every variable are immutable
    let mut guess = String::new();

    // & : reference :-)
    // &mut : mutable reference
    // coding style : one function call per line (...)
    io::stdin().read_line(&mut guess)
        .expect("Failed to read line");

    // (In that particular case ?) read_line returns a value—in this case, an io::Result
    // calling the expect method of the returned Result instance
    // which from the doc:
    // Unwraps a result, yielding the content of an Ok.
    // Panics if the value is an Err, with a panic message including the passed message,
    //        and the content of the Err.

    println!("You guessed: {}", guess);
    println!("Or in another word {} was guessed {}", guess,"coucou");
}
