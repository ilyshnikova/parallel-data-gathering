package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

func f(done chan bool) {
	resp, err := http.Get("http://example.com/")

	if err != nil {
		log.Fatal("failed")
	}
	body, err := ioutil.ReadAll(resp.Body)
	fmt.Printf("body= %q\n\n", body)
	done <- true
}

func main() {
	var done = make(chan bool)

	go f(done)
	go f(done)
	go f(done)

	for i := 0; i < 3; i++ {
		<-done
	}
}
