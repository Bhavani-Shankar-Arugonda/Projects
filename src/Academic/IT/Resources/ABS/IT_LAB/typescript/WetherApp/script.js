"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const axios_1 = __importDefault(require("axios"));
console.log("JavaScript is running!");
const cityInput = document.getElementById("cityInput");
const fetchWeatherBtn = document.getElementById("fetchWeather");
const weatherDataDiv = document.getElementById("weatherData");
const API_KEY = "9c80e374b8b7b0e72d92111c0a733883";
const API_URL = "https://api.openweathermap.org/data/2.5/weather";
const getWeather = (city) => __awaiter(void 0, void 0, void 0, function* () {
    try {
        const response = yield axios_1.default.get(`${API_URL}?q=${city}&units=metric&appid=${API_KEY}`);
        displayWeather(response.data);
    }
    catch (error) {
        weatherDataDiv.innerHTML = `<p style="color:red;">City not found. Please try again.</p>`;
    }
});
const displayWeather = (data) => {
    weatherDataDiv.innerHTML = `
        <h2>Weather in ${data.name}</h2>
        <p>Temperature: ${data.main.temp}°C</p>
        <p>Humidity: ${data.main.humidity}%</p>
        <p>Condition: ${data.weather[0].description}</p>
    `;
};
fetchWeatherBtn.addEventListener("click", () => {
    const city = cityInput.value.trim();
    if (city) {
        getWeather(city);
    }
    else {
        weatherDataDiv.innerHTML = `<p style="color:red;">Please enter a city name.</p>`;
    }
});
