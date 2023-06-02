#!/usr/bin/env -S julia --color=yes --startup-file=no

N = 50

struct Eq
    a
    b
    c
end

function solve(eq::Eq)
    if eq.b^2 == 4eq.a*eq.c
        return Any[1 -eq.b/2eq.a]
    elseif eq.b^2 > 4eq.a*eq.c
        d = √(eq.b^2 - 4eq.a*eq.c)
        return Any[2 (-eq.b+d)/2eq.a (-eq.b-d)/2eq.a]
    else
        return Any[0]
    end
end

function main()
    open("task.csv", "w") do task
        open("answers.csv", "w") do res
            for i = 1:N
                a = (rand ∘ rand)([-9:-1, 1:9])
                b, c = rand(-9:9, 2)
                answer = (string ∘ solve ∘ Eq)(a,b,c)[5:end-1]
                println(task, "$a $b $c")
                println(res, answer)
            end
        end
    end
end


if abspath(PROGRAM_FILE) == @__FILE__
    main()
end


