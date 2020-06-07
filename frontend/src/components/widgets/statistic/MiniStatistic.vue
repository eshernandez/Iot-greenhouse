<template>
<v-card>
    <v-card-text class="pa-0">
        <v-container class="pa-0">
            <div class="layout row ma-0">
                <div class="sm6 xs6 flex">
                    <div class="layout column ma-0 justify-center align-center">
                        <v-icon size="56px" :color="color">{{icon}}</v-icon>
                        <!-- <v-tooltip bottom>
                            <v-icon slot="activator" dark color="primary">home</v-icon>
                            <v-btn tabindex="0" fab outline small class="white--text" :color="colorBtn"
                             @click="fetchReq()">
                            <span>{{btnTitle}}  </span>
                            </v-btn>    
                        </v-tooltip> -->
                        <v-tooltip v-model="show" bottom>
                            <v-btn :loading="busy" :disabled="busy" slot="activator" icon @click="fetchReq()">
                                <v-icon :color="colorBtn">{{iconBtn}}</v-icon>
                            </v-btn>
                            <span>{{btnTitle}}</span>
                        </v-tooltip>
                    </div>
                </div>
                <div class="sm6 xs6 flex text-sm-center py-3 white--text" :class="color">
                    <div class="headline">{{ title }}</div>
                    <span class="caption">{{ subTitle }}</span>
                </div>
            </div>
        </v-container>
    </v-card-text>
</v-card>
</template>

<script>
export default {
    props: {
        icon: String,
        title: String,
        subTitle: String,
        color: String,
        btnTitle: String,
        hRef: String,
        colorBtn: String,
        iconBtn:String
    },
    data() {
        return {
            busy:false,
            stateLed: {
                state: false
            },
            show:false
        }
    },
    methods: {
        async fetchReq() {
            this.stateLed = true
            this.busy=true
            // console.log(this.stateLed);
            
            const url = this.hRef
            await fetch(url,{
                    method: 'POST',
                    mode: "cors",
                    body: this.stateLed,
                    // headers: {
                    //     'Content-Type': 'application/json',
                    // }
                }).then(res => res.json())
                .catch(error =>{
                     this.busy=false
                     console.error('Error:', error)
                     this.$emit('switchSnackbar', {color: 'error', timeout:5000, text: `Peticion no completada, intente de nuevo  ${this.btnTitle}`, state:true})
                     })
                .then(response => {
                    console.log(response)
                    this.busy=false
                    if(response!==undefined){
                     this.$emit('switchSnackbar', {color: 'success', timeout:3000, text:  `Peticion Exitosa, ${this.btnTitle} `, state:true})
                    }
                    // this.stateLed.state = false;
                });
        }
    },
};
</script>
