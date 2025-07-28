// Ported from Daves AI generated c++ code.

use std::env::args;

struct TimeToFull {
    perhour: f64,
    current_percent: f64,
}

impl TimeToFull {
    fn new(perhour: f64, current_percent: f64) -> Result<Self, String> {
        if perhour <= 0.1 || !(0.0..=100.0).contains(&current_percent) {
            return Err("Invalid input".to_string());
        }
        Ok(TimeToFull {
            perhour,
            current_percent,
        })
    }

    fn calculate_time_to_full(&self) -> f64 {
        let remaining = 100.0 - self.current_percent;
        remaining / self.perhour
    }
}

/* We expect 2 arguments. */
fn main() -> Result<(), String> {
    if args().len() != 3 {
        return Err(format!(
            "Usage: {} <percent_per_hour> <current_percent>",
            args().next().unwrap()
        ));
    }

    let ttf = TimeToFull::new(
        args().nth(1).unwrap().parse().unwrap(),
        args().nth(2).unwrap().parse().unwrap(),
    )
    .unwrap();

    println!("Time to full: {:.1} hours", ttf.calculate_time_to_full());

    Ok(())
}
