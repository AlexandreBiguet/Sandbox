extern crate rand;

use rand::Rng;
use std::cmp::Ordering;
use std::io;

fn main() {

    let secret_number = rand::thread_rng().gen_range(1, 101);

    println!("Guess the number in [1, 100][Hint {}]", secret_number);

    loop {
        let mut guess = String::new();

        // Error handling

        io::stdin().read_line(&mut guess)
            .expect("Failed to read line");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("A number please");
                continue;
            },
        };

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                println!("quit");
                break;
            },
        }
    }

}
