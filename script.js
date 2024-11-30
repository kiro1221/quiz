let selectedOption = null;

function createBtnAnswer(options, container) {
    const btnDiv = document.createElement("div");
    btnDiv.className = "answerBtn";
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
function createBtn(questionType, topicName, id, selectedOption) {
    const submit = document.createElement("button");
    submit.textContent = "submit";
    submit.className = "submitBtn";
    submit.onclick = () => submitHandler(questionType, topicName, id, selectedOption);
    container.appendChild(submit);
}
function submitHandler(questionType, topicName, id, selectedOption){
        console.log("Question Type:", questionType);
        console.log("Topic Name:", topicName);
        console.log("Question ID:", id);
        console.log("Selected Option:", selectedOption);
}
function createFill() {
    const inputText = document.createElement("input");
    inputText.type = "text";
    inputText.placeholder = "input answer";
    inputText.className = "inputAns";
    inputText.required = true;
    container.appendChild(inputText);
}
function sendData(questionType, topicName, id, selectedOption) {
    //TODO:ADD PARAMS TO THIS Function so you can just put it in the fetchQuizData and pass everything in
    console.log(questionType);
    console.log(topicName);
    console.log(id);
    if (selectedOption) {
        console.log(selectedOption);
    }

    //   const { questionType, topicName } = quizData;
    //   const url = `http://localhost:9100/seleep/answer`;
    //   const data = {
    //     id: 1,
    //     type: "TF",
    //     topic: "Solid",
    //     answer: ["True"],
    //   };

    //   try {
    //     const response = await fetch(url, {
    //       method: "POST",
    //       headers: {
    //         "Content-Type": "application/json",
    //       },
    //       body: JSON.stringify(data),
    //     });

    //     if (!response.ok) {
    //       throw new Error(`HTTP error! status: ${response.status}`);
    //     }
    //     const result = await response.json();
    //     console.log("Success:", result);
    //   } catch (error) {
    //     console.error("Error:", error);
    //   }
}
async function fetchQuizData() {
    let container = document.getElementById("container");
    let side = document.getElementById("side");

    try {
        const Random = "Random";
        const Solid = "Solid";
        const TF = "TF";
        const MC = "MC";
        const FILL = "FILL";
        const MATCH = "MATCH";
        const endpointUrl = `http://localhost:9100/seleep/questions?topic=${Random}&type=${FILL}`;
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
        let questionType = quizData.questionType;
        let topicName = quizData.topicName;
        let id = quizData.id;
        let options = quizData.options;
        if (quizData.questionType === "MATCH") {
            header.innerHTML = `You're getting quizzed on ${quizData.topicName} <br> This is a ${quizData.questionType} question`;
            container.appendChild(questionText);
            side.appendChild(header);
            //createBtn();
        } else if (quizData.questionType === "MC") {
            header.innerHTML = `You're getting quizzed on ${quizData.topicName} <br> This is a ${quizData.questionType} question`;
            container.appendChild(questionText);
            side.appendChild(header);
            createBtnAnswer(options);
            // createBtn();
        } else if (quizData.questionType === "TF") {
            header.innerHTML = `You're getting quizzed on ${quizData.topicName} <br> This is a ${quizData.questionType} question`;
            container.appendChild(questionText);
            side.appendChild(header);
            createBtnAnswer(options,container);
            // createBtn();
        } else if (quizData.questionType === "FILL") {
            header.innerHTML = `You're getting quizzed on ${quizData.topicName} <br> This is a ${quizData.questionType} question`;
            container.appendChild(questionText);
            createFill();
            side.appendChild(header);
            //createBtn();
        }
        createBtn(questionType, topicName, id, selectedOption);
    } catch (error) {
        console.error("Error fetching quiz data:", error);
    }
}
document.addEventListener("DOMContentLoaded", fetchQuizData);
