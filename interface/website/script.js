const runButton = document.getElementById('run-button');
const maturationCheckbox = document.getElementById('maturation');
const maturationParamsBlock = document.getElementById('maturation-params-block');

const resultsContainer = document.getElementById('results-container');
const recommendationText = document.getElementById('recommendation-text'); 
const resultsTableBody = document.getElementById('results-tbody');

const chartCanvas = document.getElementById("loss-chart");
const progressChartCanvas = document.getElementById("progress-chart");
const formInputs = document.querySelectorAll('input[type="number"], input[type="text"]');

const helpButton = document.getElementById('help-button');
const helpModal = document.getElementById('help-modal');
const closeButton = document.querySelector('.close-button');
let myChart = null;
let progressChart = null;
let backendApi;

const STRATEGY_NAMES = {
    'greedy': 'Жадная',
    'thrifty': 'Бережливая',
    'greedy_thrifty': 'Жадно-бережливая',
    'thrifty_greedy': 'Бережливо-жадная',
    'median': 'Медианная',
    'optimal': 'Оптимальная'
};

function getRussianName(englishName) {
    return STRATEGY_NAMES[englishName] || englishName;
}

function openHelpModal() {
    helpModal.classList.remove('hidden');
    setTimeout(() => helpModal.classList.add('visible'), 10); 
}

function closeHelpModal() {
    helpModal.classList.remove('visible');
    setTimeout(() => helpModal.classList.add('hidden'), 300); 
}

// ИНИЦИАЛИЗАЦИЯ И ВАЛИДАЦИЯ
window.onload = function() 
{
    new QWebChannel(qt.webChannelTransport, function(channel) {
        backendApi = channel.objects.backend;
        console.log("Связь с Python установлена!");
    });

    formInputs.forEach(input => {
        validateInput(input);
        input.addEventListener('input', () => validateInput(input));
    });
    if (helpButton) {
        helpButton.addEventListener('click', openHelpModal);
    }
    if (closeButton) {
        closeButton.addEventListener('click', closeHelpModal);
    }
    window.addEventListener('click', (event) => {
        if (event.target === helpModal) {
            closeHelpModal();
        }
    });
};


maturationCheckbox.addEventListener('change', () => {
    if (maturationCheckbox.checked)
    {
        maturationParamsBlock.classList.remove('hidden');
    }
    else
    {
        maturationParamsBlock.classList.add('hidden');
    }
    maturationParamsBlock.querySelectorAll('input').forEach(validateInput);
});

function validateInput(inputElement) {
    const value = parseFloat(inputElement.value);
    const id = inputElement.id;
    let isValid = true;
    let errorMessage = '';
    let isWarning = false;

    // Проверка 1: Пустое или невалидное число
    if (inputElement.value.trim() === '' || isNaN(value)) {
        isValid = false;
        errorMessage = 'Поле должно быть заполнено числом.';
    }
    
    if (isValid) {
        // Проверка 2: t, n, v (Целые и положительные)
        if (id === 't' || id === 'n' || id === 'v') {
            if (value !== Math.floor(value) || value < 1) {
                isValid = false;
                errorMessage = 'Введите целое число больше 0.';
            }
        }
        
        // Проверка 3: Диапазоны (alpha-min/max, beta-1/2, beta-max)
        if (id.startsWith('alpha-') || id.startsWith('beta-')) {
            // Значение должно быть строго больше 0
            if (value <= 0) {
                 isValid = false;
                 errorMessage = 'Введите число больше 0.';
            }
            // Дополнительная валидация на верхнюю границу (например, не более 5)
            if (value > 5.0 && id !== 'beta-max') {
                 isWarning = true;
                 errorMessage = 'Внимание: Значение коэффициента выше 5.0.';
            }
        }

        // Проверка 4: Предупреждение о больших числах (для T и n)
        if (id === 't' && value > 1000) {
            isWarning = true;
            errorMessage = 'Внимание: Количество экспериментов (T) больше 1000 может вызвать задержки.';
        }
        if (id === 'n' && value > 50) {
            isWarning = true;
            errorMessage = 'Внимание: Количество этапов (n) больше 50 может вызвать задержки.';
        }
    }


    // Применение стилей
    if (!isValid) {
        inputElement.style.borderColor = 'red';
        inputElement.title = errorMessage; 
    } else if (isWarning) {
        inputElement.style.borderColor = 'orange';
        inputElement.title = errorMessage;
    } else {
        inputElement.style.borderColor = 'green'; 
        inputElement.title = 'Данные корректны.';
    }
    
    if (inputElement.value.trim() === '') {
        inputElement.style.borderColor = ''; 
        inputElement.title = '';
    }

    return isValid;
}

function validateAllInputs() {
    let allValid = true;
    const requiredInputs = Array.from(formInputs).filter(input => {
        // Учитываем только видимые поля v и beta-max, если активно дозаривание
        if (input.id === 'v' || input.id === 'beta-max') {
            return maturationCheckbox.checked;
        }
        return true;
    });

    requiredInputs.forEach(input => {
        if (!validateInput(input)) {
            allValid = false;
        }
    });

    return allValid;
}

async function handleRunClick()
{
    if (!backendApi)
    {
        alert("Связь с вычислительным ядром еще не установлена. Пожалуйста, подождите.");
        return;
    }
    
    // Валидация перед отправкой
    if (!validateAllInputs()) {
        alert("Пожалуйста, исправьте некорректно заполненные поля.");
        return;
    }

    const params = 
    {
        t: parseInt(document.getElementById('t').value),
        n: parseInt(document.getElementById('n').value),
        alpha_min: parseFloat(document.getElementById('alpha-min').value),
        alpha_max: parseFloat(document.getElementById('alpha-max').value),
        beta_1: parseFloat(document.getElementById('beta-1').value),
        beta_2: parseFloat(document.getElementById('beta-2').value),
        concentrated: document.getElementById('dist-concentrated').checked,
        inorganic: document.getElementById('inorganic').checked,
        maturation: maturationCheckbox.checked,
    };

    if (params.maturation)
    {
        params.v = parseInt(document.getElementById('v').value);
        params.beta_max = parseFloat(document.getElementById('beta-max').value);
    } 
    else 
    {
        params.v = 1; 
        params.beta_max = 1.0;
    }
    
    runButton.disabled = true;
    runButton.textContent = "Выполняется...";

    try 
    {
        const paramsJsonString = JSON.stringify(params);

        const resultJsonString = await new Promise(resolve => {
            backendApi.run_simulation(paramsJsonString, resolve);
        });

        const results = JSON.parse(resultJsonString);

        if (results.error || results.error_type)
        {
            alert("Произошла ошибка на стороне C++: " + (results.error || results.message));
        } else 
        {
            displayResults(results);
        }
    } catch (error)
    {
        console.error("Произошла ошибка при вызове Python:", error);
        alert("Произошла критическая ошибка. Подробности в консоли.");
    } finally
    {
        runButton.disabled = false;
        runButton.textContent = "Запустить симуляцию";
    }
}


function displayResults(data)
{
    // 1. Фильтруем стратегии: исключаем 'optimal' для отображения
    const strategiesToDisplay = Object.keys(data).filter(key => key !== 'optimal');
    
    let bestStrategyKey = '';
    let minLoss = Infinity;

    // Определяем лучшую стратегию
    for (const key of strategiesToDisplay)
    {
        if (data[key].avg_loss < minLoss)
        {
            minLoss = data[key].avg_loss;
            bestStrategyKey = key;
        }
    }

    if (bestStrategyKey) {
        const russianName = getRussianName(bestStrategyKey);
        recommendationText.innerHTML = `<strong>${russianName}</strong> (${bestStrategyKey})`; 
    } else {
        recommendationText.textContent = 'Нет данных';
    }
    
    // 2. Данные для графиков и таблицы
    const lossesToDisplay = strategiesToDisplay.map(key => data[key].avg_loss);
    
    updateTable(strategiesToDisplay, lossesToDisplay);
    drawOrUpdateLossChart(strategiesToDisplay, lossesToDisplay);
    
    // 3. Вызов нового графика прогресса
    drawOrUpdateProgressChart(data); 

    resultsContainer.classList.remove('hidden');
}


function updateTable(names, losses)
{
    resultsTableBody.innerHTML = '';

    for (let i = 0; i < names.length; i++)
    {
        const englishName = names[i];
        const russianName = getRussianName(englishName);
        const loss = losses[i];
                
        const row = document.createElement('tr');
        row.innerHTML = `<td>${russianName} (${englishName})</td><td>${(loss * 100).toFixed(2)} %</td>`;
        resultsTableBody.appendChild(row);
    }
}


// ФУНКЦИИ ДЛЯ ГРАФИКОВ
function drawOrUpdateLossChart(labels, losses)
{
    const russianLabels = labels.map(label => getRussianName(label));
    const dataForChart = losses.map(loss => loss * 100);

    if (myChart)
    {
        myChart.data.labels = russianLabels;
        myChart.data.datasets[0].data = dataForChart;  
        myChart.update();
    }
    else
    {
        const chartData = {
            labels: russianLabels,
            datasets: [{
                label: 'Средние относительные потери (%)',
                data: dataForChart,
                backgroundColor: 'rgba(54, 162, 235, 0.6)',
                borderColor: 'rgba(54, 162, 235, 1)',
                borderWidth: 1
            }]
        };

        const config = {
            type: 'bar',
            data: chartData,
            options: {
                responsive: true,
                scales: {
                    y: {
                        beginAtZero: true,
                        title: {
                            display: true,
                            text: 'Потери (%)'
                        }
                    },
                    x: {
                        ticks: {
                            maxRotation: 45,
                            minRotation: 45
                        }
                    }
                },
                plugins: {
                    legend: {
                        display: false
                    }
                }
            }
        };

        myChart = new Chart(chartCanvas, config);
    }
}


function drawOrUpdateProgressChart(data) {
    const strategiesToDisplay = Object.keys(data).filter(key => key !== 'optimal');
    
    const nStages = data[strategiesToDisplay[0]] && data[strategiesToDisplay[0]].progress ? data[strategiesToDisplay[0]].progress.length : 0;
    const stageLabels = Array.from({ length: nStages }, (_, i) => `Этап ${i + 1}`);
    
    const COLORS = [
        'rgb(255, 99, 132)',
        'rgb(54, 162, 235)',
        'rgb(255, 205, 86)',
        'rgb(75, 192, 192)',
        'rgb(153, 102, 255)'
    ];

    const datasets = strategiesToDisplay.map((key, index) => {
        const loss_progress = data[key].progress || [];
        
        let cumulativeLoss = 0;
        const cumulativeData = loss_progress.map(stepLossRatio => {
            cumulativeLoss += stepLossRatio * 100; 
            return cumulativeLoss;
        });

        return {
            label: getRussianName(key),
            data: cumulativeData,
            borderColor: COLORS[index % COLORS.length],
            backgroundColor: COLORS[index % COLORS.length] + '40',
            tension: 0.1,
            fill: false,
            pointRadius: 3
        };
    });

    if (progressChart) {
        progressChart.data.labels = stageLabels;
        progressChart.data.datasets = datasets;
        progressChart.update();
    } else {
        const config = {
            type: 'line',
            data: {
                labels: stageLabels,
                datasets: datasets,
            },
            options: {
                responsive: true,
                plugins: {
                    legend: {
                        position: 'top',
                    },
                    title: {
                        display: false,
                        text: 'Прогресс достижения результата'
                    }
                },
                scales: {
                    x: {
                        title: {
                            display: true,
                            text: 'Этапы (n)'
                        }
                    },
                    y: {
                        title: {
                            display: true,
                            text: 'Накопительный результат (% от максимума)' 
                        },
                        beginAtZero: true
                    }
                }
            }
        };

        progressChart = new Chart(progressChartCanvas, config);
    }
}

runButton.addEventListener('click', handleRunClick);
