package main

import (
	"fmt"
	"log"
	"net/http"
	"os"
	"time"
)

func handler(w http.ResponseWriter, r *http.Request) {
	log.Println("Starting to serve")
	time.Sleep(2 * time.Second)
	fmt.Fprintf(w, "Currency is now 12342.23487")
	log.Println("Done serving")
}

func main() {
	http.HandleFunc("/", handler)
	http.ListenAndServe(":"+string(os.Args[1]), nil)
}
