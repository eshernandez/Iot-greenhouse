<template>
<!-- <div class="home"> -->
<!-- Temperatura -->
<v-container grid-list-xl fluid>
    <v-layout row wrap>
        <!-- <v-flex xs12> -->
                <!-- <v-btn dark @click.native="snackbar.state = true">Close</v-btn> -->
                <v-snackbar :timeout="snackbar.timeout" :color="snackbar.color" v-model="snackbar.state">
                {{ snackbar.text }}
                <v-btn dark flat @click.native="snackbar.state = false">Cerrar</v-btn>
            </v-snackbar>
        <!-- </v-flex> -->
        <v-flex md4 xs12>
            <v-widget title="Temperatura" content-bg="white">
                <div slot="widget-content">
                    <!-- {{data[50]}} -->
                    <mini-statistic @switchSnackbar="switchSnackbar($event)" icon="brightness_medium" :title="realTimeTemperature" sub-title="Grados Centigrados" color="red" btnTitle="Encender Aspersor" hRef="http://186.87.251.184/sprinkler" iconBtn="build" colorBtn="red">
                    </mini-statistic>
                </div>
            </v-widget>
        </v-flex>
        <!-- Humedad -->
        <v-flex md4 xs12>
            <v-widget title="Humedad" content-bg="white">
                <div slot="widget-content">
                    <!-- {{data[41]}} -->
                    <mini-statistic @switchSnackbar="switchSnackbar($event)" icon="local_drink" :title="realTimeHumidity" sub-title="Porciento" color="light-blue" btnTitle="Apagar Bomba" hRef="http://186.87.251.184/bomb" iconBtn="build" colorBtn="light-blue"></mini-statistic>
                </div>
            </v-widget>
        </v-flex>
        <!--Presion -->
        <v-flex md4 xs12>
            <v-widget title="Presion" content-bg="white">
                <div slot="widget-content">
                    <!-- {{data[42]}} -->
                    <mini-statistic @switchSnackbar="switchSnackbar($event)" icon="cloud" :title="realTimePressure" sub-title="Libra por pulgada cuadrada" color="light-green" btnTitle="Liberar valvula" hRef="http://186.87.251.184/valve" iconBtn="build" colorBtn="light-green"></mini-statistic>
                </div>
            </v-widget>
        </v-flex>
        <v-flex xs12>
            <v-card>
                <line-chart :data="linearMultipleChartdata" :colors="['#f44336','#03a9f4','#8bc34a']" xtitle="Hora" ytitle="Medida"></line-chart>
            </v-card>
        </v-flex>
    </v-layout>
</v-container>
<!-- </div> -->
</template>

<script>
// @ is an alias to /src
import VWidget from "@/components/VWidget";
// import LineChart from "@/components/chart/LineChart.vue";
import MiniStatistic from '@/components/widgets/statistic/MiniStatistic';
// import Dashboard from '@/components/Dashboard.vue'

export default {
    name: 'Home',
    components: {
        VWidget,
        MiniStatistic
    },
    data() {
        return {
            fetch: null,
            data: null,
            snackbar:{
                state: false,
                color: 'error',
                timeout: 2000,
                text: ''
            },
            sensors: {
                temperature: null,
                humidity: null,
                pressure: null
            },
            realTimeSensors: {
                temperature: "",
                humidity: "",
                pressure: ""
            },
            linearMultipleChartdata: [{
                    name: 'Temperatura',
                    data: {}
                },
                {
                    name: 'Humedad',
                    data: {

                    }
                },
                {
                    name: 'Presion',
                    data: {

                    }
                }
            ]
        };
    },
    watch: {
        fetch: {
            handler(newVal) {
                let date = new Date();
                // console.log(this.linearMultipleChartdata);
                // console.log(`${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`);
                // console.log(`${date.getHours()}:${date.getMinutes()}:${date.getSeconds()} bip bip, datos en tiempo real:`, newVal);
                if (newVal!==undefined) {
                    newVal.forEach((sensor) => {
                        // if(sensor.type !== undefined){
                            // console.log(this.realTimeSensors.temperature)
                    // console.log(sensor.type)
                    switch (sensor.type) {
                        case 'temperature':
                            this.realTimeSensors.temperature = sensor
                            this.linearMultipleChartdata[0].data[`${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`] = sensor.value
                            //   this.linearMultipleChartdata[0].data = { `${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`: sensor }

                            // console.log(this.realTimeSensors.temperature)
                            break;
                        case "humidity":
                            this.realTimeSensors.humidity = sensor
                            this.linearMultipleChartdata[1].data[`${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`] = sensor.value
                            // console.log(this.realTimeSensors.humidity)
                            break;
                        case "pressure":
                            this.realTimeSensors.pressure = sensor
                            this.linearMultipleChartdata[2].data[`${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`] = sensor.value
                            // console.log(this.realTimeSensors.pressure=sensor)
                            break;

                        default:
                            this.realTimeSensors.temperature = ''
                            this.realTimeSensors.humidity = ''
                            this.realTimeSensors.pressure = ''
                            console.log("error");
                            break;
                    }
                    // }
                });
                }
            }
        },
    },
    methods: {

        switchSnackbar(data){
            // this.snackbar.state = false
            this.snackbar.state = data.state 
            this.snackbar.color = data.color
            this.snackbar.timeout = data.timeout
            this.snackbar.text = data.text
        },

        async requestServer() {
            // console.log("hola");
            // http://localhost:3000/api/posts
            await fetch(`http://13.65.32.226:3300/api/postsServerIot`, {
                    method: "GET",
                    mode: "cors"
                })
                .then(response => response.json())
                .then((response) =>{
                    if (response!=undefined) {
                        this.fetch = response
                    }
                    })
        },
        // async getPosts(){
        // await this.data.array.forEach(sensor => {
        //   // console.log(sensor);

        // });
        // }
    },
    computed: {
        linearMultipleChartdataComputed: function () {
            return this.linearMultipleChartdata;
        },
        realTimeTemperature: function () {
            return this.realTimeSensors.temperature ? `${this.realTimeSensors.temperature.value}${this.realTimeSensors.temperature.unit}` : 'Cargando...'
        },
        realTimeHumidity: function () {
            return this.realTimeSensors.humidity ? `${this.realTimeSensors.humidity.value}${this.realTimeSensors.humidity.unit}` : 'Cargando...'
        },
        realTimePressure: function () {
            return this.realTimeSensors.pressure ? `${this.realTimeSensors.pressure.value}${this.realTimeSensors.pressure.unit}` : 'Cargando...'
        },
        linearMultipleChartdatas: function () {
            // console.log("hola")
            return this.linearMultipleChartdata;
        }
    },
    mounted() {
        // this.proccesingRequest();
        setInterval(() => {
            this.requestServer();
        }, 5000);

        // this.getPosts();
    }

}
</script>
