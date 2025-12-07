const runButton = document.getElementById('run-button');
const maturationCheckbox = document.getElementById('maturation');
const maturationParamsBlock = document.getElementById('maturation-params-block');

const resultsContainer = document.getElementById('results-container');
const recommendationText = document.getElementById('recommendation-text');
const resultsTableBody = document.getElementById('results-tbody');

const chartCanvas = document.getElementById("loss-chart")

let myChart = null;
let backendApi;

window.onload = function() 
{
    new QWebChannel(qt.webChannelTransport, function(channel) {
        backendApi = channel.objects.backend;
        console.log("Связь с Python установлена!");
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
});


async function handleRunClick()
{
    if (!backendApi)
    {
        alert("Связь с вычислительным ядром еще не установлена. Пожалуйста, подождите.");
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

    console.log("Собранные данные для отправки: ", JSON.stringify(params, null, 2));

    runButton.disabled = true;
    runButton.textContent = "Выполняется...";

    try 
    {
        const paramsJsonString = JSON.stringify(params);

        const resultJsonString = await new Promise(resolve => {
            backendApi.run_simulation(paramsJsonString, resolve);
        });

        const results = JSON.parse(resultJsonString);

        console.log("Полученные результаты:", results);

        if (results.error)
        {
            alert("Произошла ошибка на стороне C++: " + results.error);
        } else if (results.error_type) 
        {
            alert(`Ошибка валидации от С++: не найдено обязательное поле '${results.message}'`);
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
    const names = Object.keys(data);
    const losses = names.map(name => data[name].avg_loss);

    let bestStrategy = '';
    let minLoss = Infinity;

    for (const name of names)
    {
        if (name !== 'optimal' && data[name].avg_loss < minLoss)
        {
            minLoss = data[name].avg_loss;
            bestStrategy = name;
        }
    }

    recommendationText.textContent = bestStrategy || 'Нет данных';
    updateTable(names, losses);
    drawOrUpdateChart(names, losses);

    resultsContainer.classList.remove('hidden');
}


function updateTable(names, losses)
{
    resultsTableBody.innerHTML = '';

    for (let i = 0; i < names.length; i++)
    {
        const name = names[i];
        const loss = losses[i];

        const row = document.createElement('tr');
        row.innerHTML = `<td>${name}</td><td>${(loss * 100).toFixed(2)} %</td>`;
        resultsTableBody.appendChild(row);
    }
}


function drawOrUpdateChart(labels, losses)
{
    const dataForChart = losses.map(loss => loss * 100);

    if (myChart)
    {
        myChart.data.labels = labels;
        myChart.data.datasets[0].data = dataForChart;   
        myChart.update();
    }
    else
    {
        const chartData = {
            labels: labels,
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

runButton.addEventListener('click', handleRunClick);
