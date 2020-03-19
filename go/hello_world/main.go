package main

import (
	"net/http"
	"os"
)

func main() {

	var owmApiKey string = os.Getenv("OPEN_WEATHER_MAP_API_KEY")


	http.HandleFunc("/", helloHandler)
	http.ListenAndServe(":8080", nil)
}

func helloHandler(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte("Hello, World"))
}
