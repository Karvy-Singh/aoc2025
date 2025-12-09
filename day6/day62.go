package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	file, err := os.Open("inputfile.txt")
	if err != nil {
		fmt.Println("file not found:", err)
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	var lines []string
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}

	line1 := lines[0]
	line2 := lines[1]
	line3 := lines[2]
	line4 := lines[3]
	opss := lines[4]
	ops := make([]string, 0)
	for _, op := range strings.Fields(opss) {
		ops = append(ops, op)
	}

	colidx := make([]int, 0)
	for i, ch := range opss {
		if ch == '*' || ch == '+' {
			colidx = append(colidx, i)
		}
	}

	markCols := func(s string, cols []int) string {
		b := []byte(s)
		for _, idx := range cols {
			pos := idx - 1
			if pos >= 0 && pos < len(b) {
				b[pos] = 'x'
			}
		}
		return strings.ReplaceAll(string(b), " ", "0")
	}

	line1 = markCols(line1, colidx)
	line2 = markCols(line2, colidx)
	line3 = markCols(line3, colidx)
	line4 = markCols(line4, colidx)

	fmt.Println(line1)
	fmt.Println(line2)
	fmt.Println(line3)

	nums := strings.Split(line1+"x"+line2+"x"+line3+"x"+line4, "x")

	total := 0
	col := len(ops)

	for i, op := range ops {
		localsum := 0
		localmul := 1

		if op == "*" {
			maxlen := 0
			for j := i; j < len(nums); j += col {
				if len(nums[j]) > maxlen {
					maxlen = len(nums[j])
				}
			}
			formnum := make([]int, maxlen)
			for j := i; j < len(nums); j += col {
				idx := 0
				// fmt.Println(nums[j])
				for i := len(nums[j]) - 1; i >= 0; i-- {
					digit, err := strconv.Atoi(string(nums[j][i]))
					// fmt.Printf("%d ", digit)
					if err != nil {
						continue
					}

					formnum[idx] = formnum[idx]*10 + digit
					idx += 1
				}
			}

			for _, num := range formnum {
				if num%10 == 0 {
					for num%10 == 0 {
						num = num / 10
					}
				}
				localmul *= num
				fmt.Println(num)
			}
			total += localmul
		} else if op == "+" {
			maxlen := 0
			for j := i; j < len(nums); j += col {
				if len(nums[j]) > maxlen {
					maxlen = len(nums[j])
				}
			}

			formnum := make([]int, maxlen)
			for j := i; j < len(nums); j += col {
				idx := 0
				// fmt.Println(nums[j])

				for i := len(nums[j]) - 1; i >= 0; i-- {
					digit, err := strconv.Atoi(string(nums[j][i]))
					// fmt.Printf("%d ", num)
					if err != nil {
						continue
					}

					formnum[idx] = formnum[idx]*10 + digit
					idx += 1
				}
			}
			for _, num := range formnum {
				if num%10 == 0 {
					for num%10 == 0 {
						num = num / 10
					}
				}
				localsum += num
				fmt.Println(num)
			}
			total += localsum

		}

	}
	fmt.Println(total)
}
