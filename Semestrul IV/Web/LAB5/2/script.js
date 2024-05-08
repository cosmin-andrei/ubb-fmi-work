$(document).ready(function() {
    $('#myForm').on('submit', function(event) {
        event.preventDefault();

        if (checkForm()) {
            alert('Formularul a fost completat corect și a fost trimis.'); // Afișăm un mesaj de succes
            $('#myForm')[0].reset(); // Resetează formularul
        }
    });

    function checkEmail(email) {
        let emailPattern = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;
        return emailPattern.test(email);
    }

    function checkAge(age) {
        return age >= 18 && age <= 80;
    }

    function checkName(name) {
        return name.length >= 3 && name.length <= 50;
    }

    function checkDate(date) {
        let datePattern = /^\d{4}-\d{2}-\d{2}$/;
        return datePattern.test(date);
    }

    function checkForm() {
        let name = $('#name').val();
        let date = $('#date').val();
        let age = $('#age').val();
        let email = $('#email').val();
        let errors = false;

        $('#name, #date, #age, #email').css('border-color', '');

        if (!checkName(name)) {
            alert('Numele trebuie să aibă între 3a și 50 de caractere');
            $('#name').css('border-color', 'red');
            errors = true;
        }

        if (!checkDate(date)) {
            alert('Data trebuie să fie de forma yyyy-mm-dd');
            $('#date').css('border-color', 'red');
            errors = true;
        }

        if (!checkAge(age)) {
            alert('Vârsta trebuie să fie între 18 și 80');
            $('#age').css('border-color', 'red');
            errors = true;
        }

        if (!checkEmail(email)) {
            alert('Emailul nu este valid');
            $('#email').css('border-color', 'red');
            errors = true;
        }

        if (!errors) {
            return true;
        } else {
            return false;
        }
    }
});
