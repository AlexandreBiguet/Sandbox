# Following official doc

[https://doc.rust-lang.org/stable/book/second-edition/ch01-03-hello-cargo.html][link]

- hello world example
- hello cargo (cargo = rust build system and package manager).
  Using cargo creates a cargo.lock file which keeps tracks of the project deps.
  `% cd hello_cargo && cargo build` creates the lock file and the `target`
  (build) directory (with debug flags)
  To create a release `% cargo build --release`
- guessing_game:
  - **external dependency**, Cargo fetches the latest versions of everything from
  the registry, which is a copy of data from Crates.io. Crates.io is where
  people in the Rust ecosystem post their open source Rust projects for others
  to use. **fetching the data takes while !**
  - **multiple binaries in a single project**. Simply add the `[[bin]]`
  stuff in the toml file
  - `% cargo clean` removes the *target* directory... that sucks.
  See the `cargo-clean --help`
  - **Generating locally the doc for the packages we use !** `% cargo doc --open`
