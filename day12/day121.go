package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	file, err := os.Open("shapes.txt")
	if err != nil {
		fmt.Println("file not found")
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)

	cnt := 0
	shapearea := make([]int, 0)
	for scanner.Scan() {
		line := scanner.Text()
		if strings.HasPrefix(line, "#") || strings.HasPrefix(line, ".") {
			for _, i := range line {
				if i == '#' {
					cnt = cnt + 1
				}
			}
		} else {
			shapearea = append(shapearea, cnt)
			cnt = 0
		}
	}

	file2, err := os.Open("inputfile.txt")
	if err != nil {
		fmt.Println("file not found:", err)
		return
	}
	defer file2.Close()

	scanner2 := bufio.NewScanner(file2)
	total := 0
	for scanner2.Scan() {
		line := scanner2.Text()
		parts := strings.Split(line, ":")
		areat := strings.Split(parts[0], "x")
		area := make([]int, 0)
		for _, i := range areat {
			num, err := strconv.Atoi(i)
			if err != nil {
				continue
			}
			area = append(area, num)
		}

		gifts := strings.Fields(strings.TrimSpace(parts[1]))
		// fmt.Println(area)
		// fmt.Println(gifts)

		ar := int(area[0]) * int(area[1])
		sum := 0
		shapes := 0
		for idx, i := range gifts {
			num, err := strconv.Atoi(i)
			if err != nil {
				continue
			}
			sum += num * shapearea[idx]
			shapes += num
		}

		if sum > ar {
			continue
		}

		if ar/9 >= shapes {
			total += 1
		}

	}
	fmt.Println(total)
}
