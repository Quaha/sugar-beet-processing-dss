const fakeResponseData = {
    "names": [
        "greedy",
        "thrifty",
        "greedy_thrifty",
        "thrifty_greedy",
        "median",
        "optimal"
    ],
    "avg_loss": [2.82, 4.52, 3.15, 4.08, 3.55, 0.0],
    "avg_step_ratio": [

    ]
};


const runButton = document.getElementById('run-button');
const maturationCheckbox = document.getElementById('maturation');
const maturationParamsBlock = document.getElementById('maturation-params-block');

const resultsContainer = document.getElementById('results-container');
const recommendationText = document.getElementById('recommendation-text');
const resultsTableBody = document.getElementById('results-tbody');


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


function handleRunClick()
{
    const params = 
    {
        T: parseInt(document.getElementById('t').value),
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
        params.maturation_params = {
            v: parseInt(document.getElementById('v').value),
            beta_max: parseFloat(document.getElementById('beta-max').value)
        };
    }

    console.log("Собранные данные для отправки: ", JSON.stringify(params, null, 2));

    const results = fakeResponseData;
    console.log("Полученные результаты ", results);

    displayResults(results);
}


function displayResults(data)
{
    let bestStrategy = '';
    let minLoss = Infinity;

    for (let i = 0; i < data.names.length; i++)
    {
        const name = data.names[i];
        const loss = data.avg_loss[i];
        if (name !== 'optimal' && loss < minLoss)
        {
            minLoss = loss;
            bestStrategy = name;
        }
    }


    recommendationText.textContent = bestStrategy || 'Нет данных';

    resultsTableBody.innerHTML = '';

    for (let i = 0; i < data.names.length; i++)
    {
        const name = data.names[i];
        const loss = data.avg_loss[i];

        const row = document.createElement('tr');
        row.innerHTML = `<td>${name}</td><td>${loss.toFixed(2)} %</td>`;
        resultsTableBody.appendChild(row);
    }

    resultsContainer.classList.remove('hidden');
}


runButton.addEventListener('click', handleRunClick);