set $idx = 0

break range.c:51 if ++$idx >= 28 && $idx <= 35
    command 1
    echo @@@
    printf "%d %d %d %d\n", I.start, I.stop, I.step, I.value
    continue
end

run
