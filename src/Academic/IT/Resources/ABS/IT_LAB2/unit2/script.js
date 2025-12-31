document.getElementById("registrationForm").addEventListener("submit", function(event) {
    event.preventDefault();

    let isValid = true;

    var name = document.getElementById('name').value;
    var email = document.getElementById('email').value;
    var password = document.getElementById('password').value;
    var dob = document.getElementById('dob').value;
    var phone = document.getElementById('phone').value;

    var nameREGX = /^[a-zA-Z]+$/;
    var emailREGX = /^[a-zA-Z0-9_.±]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$/;
    var passwordREGX = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$/;
    var phoneREGX = /^\d{10}$/;

   
    if (!nameREGX.test(name)) {
        nameError.textContent = "Only alphabets are allowed!";
        isValid = false;
    } else {
        nameError.textContent = "";
    }

  
    if (!emailREGX.test(email)) {
        emailError.textContent = "Invalid email format!";
        isValid = false;
    } else {
        emailError.textContent = "";
    }

 
    if (!passwordREGX.test(password)) {
        passwordError.textContent = "Must be 8+ chars with uppercase, lowercase, number & special char!";
        isValid = false;
    } else {
        passwordError.textContent = "";
    }

    var passwordStrength = document.getElementById("passwordStrength");
    if (password.length >= 8) {
        if (/[A-Z]/.test(password) && /[a-z]/.test(password) && /\d/.test(password) && /[@$!%*?&]/.test(password)) {
            passwordStrength.textContent = "Strong";
            passwordStrength.style.color = "green";
        } else {
            passwordStrength.textContent = "Weak";
            passwordStrength.style.color = "red";
        }
    } else {
        passwordStrength.textContent = "";
    }

   
    if (dob) {
        let birthDate = new Date(dob);
        let age = new Date().getFullYear() - birthDate.getFullYear();
        if (age < 18) {
            dobError.textContent = "You must be at least 18 years old!";
            isValid = false;
        } else {
            dobError.textContent = "";
        }
    } else {
        dobError.textContent = "Please enter your date of birth!";
        isValid = false;
    }

    if (!phoneREGX.test(phone)) {
        phoneError.textContent = "Phone number must be 10 digits!";
        isValid = false;
    } else {
        phoneError.textContent = "";
    }

    
    if (isValid) {
        alert("Registration Successful!");
        document.getElementById("registrationForm").reset();
    }
});
