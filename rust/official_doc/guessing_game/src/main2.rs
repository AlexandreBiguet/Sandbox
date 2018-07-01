// rand is an external dependency
extern crate rand;

use std::io;

// The Rng trait defines methods that random number generators implement. Splendid !
use rand::Rng;

// Comparison
use std::cmp::Ordering;

fn main() {
    println!("Guess the number in [1, 100]");

    // The rand::thread_rng function will give us the particular random number generator that we’re
    // going to use: one that is local to the current thread of execution and seeded by the
    // operating system

    // the gen_range method is defined by the Rng trait that we brought into scope with the use
    // rand::Rng statement The gen_range method takes two numbers as arguments and generates a
    // random number between them. It’s inclusive on the lower bound but exclusive on the upper
    // bound, so we need to specify 1 and 101 to request a number between 1 and 100.

    let secret_number = rand::thread_rng().gen_range(1, 101);

    println!("Please input your guess. [Hint {}]", secret_number);

    let mut guess = String::new();

    io::stdin().read_line(&mut guess)
        .expect("Failed to read line");

    println!("guess before trim [{:?}]", guess);

    // Left and right operand of the cmp function must have the same type
    // Converting secret number to string or guess to integer ?

    // Converting input guess to integer

    // the variable 'guess' already exists but 'shadowing' is legal in rust
    // The trim method on a String instance will eliminate any whitespace at the beginning and end
    //
    let guess = guess.trim();
    println!("guess after trim [{:?}]", guess);

    let guess: u32 = guess.parse()
        .expect("Please type a number!");

    println!("guess after trim and parse [{:?}]", guess);

    match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => println!("You win!"),
        }

    println!("You guessed: {}", guess);
}
