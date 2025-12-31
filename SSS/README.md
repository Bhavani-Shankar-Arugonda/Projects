# Social Security Solution (SSS) App

A web-based application designed to manage apartment complex security, residents, and staff. This solution provides a comprehensive dashboard for administrators to oversee building operations, manage users (supervisors, residents), and track building details.

## Features

- **Admin Dashboard**: Centralized control panel for administrators.
- **User Management**:
  - Add/Remove Supervisors.
  - Add/Remove Residents.
  - Assign Supervisors to Buildings.
- **Property Management**:
  - Manage multiple Buildings (Add/View).
  - Manage Flats and Floors.
  - Track assignments of flats to residents.
- **Staff Management**: View and manage application staff details.
- **Role-Based Access**: Secure login for Admin, Supervisor, and Resident roles.

## Technology Stack

- **Backend**: PHP
- **Database**: MySQL
- **Web Server**: Apache (via XAMPP)
- **Frontend**: HTML, CSS, JavaScript

## Prerequisites

- **XAMPP**: A local server environment (Apache + MariaDB/MySQL + PHP). [Download XAMPP](https://www.apachefriends.org/download.html).

## Installation & Setup

1.  **Install XAMPP**
    - Download and install XAMPP for your operating system.
    - Launch the XAMPP Control Panel and start **Apache** and **MySQL**.

2.  **Setup the Database**
    - Open your browser and go to [http://localhost/phpmyadmin](http://localhost/phpmyadmin).
    - Create a new database named `The_Society_Security`.
    - Import the database schema (SQL file) if provided, or create the necessary tables manually matching the application code:
        - `users` (user_id, username, password, role, is_active)
        - `building` (building_id, building_name, building_address, city, postal_code, total_floors, total_flats, supervisor_id)
        - `flat_details` (flat_id, building_id, flat_number, floor_number, flat_type)
        - `resident_details` (resident_id, flat_id, user_id, resident_name, age, gender, phone_number, email)
        - `staff_details` (staff_id, staff_name, staff_category, phone_number, email, salary, shift_timing, is_active)
    
    *Note: Ensure the database credentials in `sss_db_config.php` match your local setup.*
    ```php
    $host = "localhost";
    $username = "root";
    $password = ""; // Default XAMPP password is empty
    $database = "The_Society_Security";
    ```

3.  **Deploy the Application**
    - Copy the project folder containing these PHP files into the XAMPP `htdocs` directory (e.g., `C:\xampp\htdocs\sss_app` or `/Applications/XAMPP/xamppfiles/htdocs/sss_app`).

4.  **Run the Application**
    - Open your web browser.
    - Navigate to `http://localhost/sss_app/sss_login_page.php` (adjust the path if you named the folder differently).
    - Log in with your credentials.

## Usage

- **Login**: Use the login page to access the system.
- **Admin**: Has full access to add buildings, assign supervisors, and manage residents.
- **Supervisor**: (Functionality based on role implementation)
- **Resident**: (Functionality based on role implementation)

## Project Structure

- `sss_admin_dashboard.php`: Main admin interface.
- `sss_resident_dashboard.php`: Resident interface.
- `sss_supervisor_dashboard.php`: Supervisor interface.
- `sss_login_page.php`: Authentication entry point.
- `sss_db_config.php`: Database connection settings.
- `sss_logout.php`: Session termination script.

## Contributing

1. Fork the repository.
2. Create feature branch (`git checkout -b feature/NewFeature`).
3. Commit changes (`git commit -m 'Add NewFeature'`).
4. Push to branch (`git push origin feature/NewFeature`).
5. Open a Pull Request.
