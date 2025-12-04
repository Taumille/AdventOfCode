use std::fs;

fn main(){
    println!("Hello World!");
    
    let contents = fs::read_to_string("input.txt")
        .expect("Couldn't read file...");

    let mut sum = 0;

    for line in contents.lines(){
        let mut biggest_combination = 0;
        for c in 0..line.len(){
            if let Some(character) = line.chars().nth(c){
                if let Some(digit) = character.to_digit(10){
                    for c2 in (c+1)..line.len(){
                        if let Some(character2) = line.chars().nth(c2){
                            if let Some(digit2) = character2.to_digit(10){
                                if digit*10+digit2 > biggest_combination {
                                    biggest_combination = digit*10+digit2;
                                }        
                            } else {
                                println!("Blorgh2");
                            }
                        } else {
                            println!("Blargh2");
                        }
                    }
                } else {
                    println!("Blorgh");
                }
            } else {
                println!("Blargh");
            }
        }
        println!("Biggest combination {}", biggest_combination);
        sum = sum + biggest_combination;
    }
    println!("Sum {}", sum);
}
