    import axios from "axios";

    console.log("JavaScript is running!");
    interface WeatherResponse {
    main: {
        temp: number;
        humidity: number;
    };
    weather: { description: string }[];
    name: string;
    }

    const cityInput = document.getElementById("cityInput") as HTMLInputElement;
    const fetchWeatherBtn = document.getElementById("fetchWeather") as HTMLButtonElement;
    const weatherDataDiv = document.getElementById("weatherData") as HTMLDivElement;

    const API_KEY = "9c80e374b8b7b0 e72d92111c0a733883";
    const API_URL = "https://api.openweathermap.org/data/2.5/weather";

    const getWeather = async (city: string): Promise<void> => {
    try {
        const response = await axios.get<WeatherResponse>(`${API_URL}?q=${city}&units=metric&appid=${API_KEY}`);
        displayWeather(response.data);
    } catch (error) {
        weatherDataDiv.innerHTML = `<p style="color:red;">City not found. Please try again.</p>`;
    }
    };

    const displayWeather = (data: WeatherResponse) => {
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
    } else {
        weatherDataDiv.innerHTML = `<p style="color:red;">Please enter a city name.</p>`;
    }
    });
