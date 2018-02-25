#!/bin/bash

q1_answer() {
    echo "All your base are belong to us" | tr a-z A-Z
}

q2_answer() {
    echo "monkeys love bananas" | sed 's/monkeys/gorillaz/'
}

q3_answer() {
    echo "     monkeys love bananas" | sed "s/^[ \t]*//"
}

q4_answer() {
    curl -sL https://yld.me/raw/yWh | grep x:0: | cut -d ':' -f 7

}

q5_answer() {
    curl -sL https://yld.me/raw/yWh | sed -e 's/\(\/bin\/bash\)\|\(\/bin\/csh\)\|\(\/bin\/tcsh\)/\/usr\/bin\/python/' | grep python 
}

q6_answer() {
    curl -sL https://yld.me/raw/yWh | awk '/[4][0-9]?[7]/'
}
