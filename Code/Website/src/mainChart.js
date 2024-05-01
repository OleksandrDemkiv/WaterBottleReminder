import Chart, { elements } from 'chart.js/auto';
import * as Utils from '../node_modules/utils'

var data, dates;
const datesElement = document.getElementById('dates');
const section = document.getElementById('section');

window.onload = async function () {
    let link = "http://192.168.77.174:80";

    const response = await fetch(link + '/get_data', {
        mode: 'cors',
        method: 'get',
        url: link,
        credentials: 'include'
    })
    data = await response.json();

    dates = Object.keys(data);
    dates.reverse();
    dates.forEach(date => {
        let option = document.createElement('option');
        option.text = date;
        option.value = date;
        datesElement.add(option);
    });

    datesElement.addEventListener('change', function () {
        var selectedValue = datesElement.options[datesElement.selectedIndex].value;
        loadData(selectedValue);
    });

    loadData(datesElement.options[0].value);
}

function loadData(value) {
    while (section.lastElementChild) {
        section.removeChild(section.lastElementChild);
    }

    const labels = Object.keys(data[value]);
    const datapoints = Object.values(data[value]);
    var sum = 0;
    datapoints.forEach(l => {
        sum += l;
    });
    
    section.innerHTML = `
        <div class="chart">
            <canvas id="mainChart"></canvas>
        </div>
        <div class="total">
            <h2>Total for the day</h2>
            <span></span>
        </div>`
    document.querySelector('.total span').innerText = sum + " litres";

    const d = {
        labels: labels,
        datasets: [
            {
                label: 'Intake by hours in litres',
                data: datapoints,
                borderColor: Utils.CHART_COLORS.green,
                fill: false,
                cubicInterpolationMode: 'monotone',
            }
        ]
    };

    new Chart(
        document.getElementById('mainChart'),
        {
        type: 'line',
        data: d,
        options: {
            responsive: true,
            plugins: {
                title: {
                    display: true,
                    text: 'Water intake for the day'
                },
            },
            interaction: {
                intersect: false,
            },
            scales: {
                x: {
                    display: true,
                    title: {
                    display: true
                }
            },
            y: {
                display: true,
                title: {
                display: true,
                text: 'Litres'
                },
                suggestedMin: 0,
                suggestedMax: 500
            }
            }
        }
})};