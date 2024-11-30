let selectedOption = null;
function createBtnAnswer(options) {
    const btnDiv = document.createElement("div");
    btnDiv.className = "answerBtn ";

    options.forEach((option, index) => {
        const button = document.createElement("button");
        button.textContent = option; 
        button.className = `option-button option-${index + 1}`; 
        button.value = option;

        button.onclick = () => {
            selectedOption = option;
            console.log(option);
        };
        btnDiv.appendChild(button);
    });
    container.appendChild(btnDiv);
}
function createBtn() {
    const submit = document.createElement("button");
    submit.textContent = "submit";
    submit.className = "submitBtn";
    submit.onclick = function () {
        const inputText = document.querySelector(".inputAns"); // Select the input field
        console.log(inputText.value); // Log the value of the input field
        if (selectedOption) {
            console.log(selectedOption); // Log the selected option
        } else {
            console.log("No option selected"); // Handle case when no option is selected
        }
        location.reload();
    };
    container.appendChild(submit);
}
function createFill(){
    const inputText = document.createElement("input")
    inputText.type = "text"
    inputText.placeholder = "input answer"
    inputText.className = "inputAns"
    inputText.required = true;
    container.appendChild(inputText)
}

async function fetchQuizData() {
    let container = document.getElementById("container");
    let side = document.getElementById("side");

    try {
        const Random = "Random";
        const Solid = "Solid"
        const TF = "TF";
        const MC = "MC";
        const FILL = "FILL";
        const MATCH = "MATCH"
        const endpointUrl = `http://localhost:9100/seleep/questions?topic=${Random}&type=${Random}`;
        const response = await fetch(endpointUrl);
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        const quizData = await response.json();
        console.log(quizData);

        let header = document.createElement("h1");
        const questionText = document.createElement("p");
        questionText.innerHTML = quizData.question;
        questionText.className = "questionText";
        let options = quizData.options;
        if (quizData.questionType === "MATCH") {
            header.innerHTML = `You're getting quizzed on ${quizData.topicName} <br> This is a ${quizData.questionType} question`;
            container.appendChild(questionText);
            side.appendChild(header);
            createMatch(options);
            createBtn();
        } else if (quizData.questionType === "MC") {
            header.innerHTML = `You're getting quizzed on ${quizData.topicName} <br> This is a ${quizData.questionType} question`;
            container.appendChild(questionText);
            side.appendChild(header);
            createBtnAnswer(options);
            createBtn();
        } else if (quizData.questionType === "TF") {
            header.innerHTML = `You're getting quizzed on ${quizData.topicName} <br> This is a ${quizData.questionType} question`;
            container.appendChild(questionText);
            side.appendChild(header);
            createBtnAnswer(options);
            createBtn();
        } else if (quizData.questionType === "FILL") {
            header.innerHTML = `You're getting quizzed on ${quizData.topicName} <br> This is a ${quizData.questionType} question`;
            container.appendChild(questionText);
            createFill()
            side.appendChild(header);
            createBtn();

        }
    } catch (error) {
        console.error("Error fetching quiz data:", error);
    }
}
// const sendData = async () => {
//     const url = `http://localhost:9100/seleep/answer`;
//     const data = {
//         id: 1,
//         type: "TF",
//         topic: "Solid",
//         answer: ["True"]
//     }; // Your JSON object

//     try {
//         const response = await fetch(url, {
//             method: "POST", // HTTP method
//             headers: {
//                 "Content-Type": "application/json", // Specify the content type
//             },
//             body: JSON.stringify(data), // Convert data to JSON string
//         });

//         if (!response.ok) {
//             throw new Error(`HTTP error! status: ${response.status}`);
//         }
//         const result = await response.json(); // Parse the JSON response
//         console.log("Success:", result); // Handle the response data
//     } catch (error) {
//         console.error("Error:", error); // Handle errors
//     }
// };

// // Call the async function
// //sendData();

document.addEventListener("DOMContentLoaded", fetchQuizData);
