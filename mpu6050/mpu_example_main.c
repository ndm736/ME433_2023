#include""

void blink();

int main() {

    // startup
    
    // init the imu
    init_mpu6050();
    
    char m_in[100]; // char array for uart data coming in
    char m_out[200]; // char array for uart data going out
    int i;
    #define NUM_DATA_PNTS 300 // how many data points to collect at 100Hz
    float ax[NUM_DATA_PNTS], ay[NUM_DATA_PNTS], az[NUM_DATA_PNTS], gx[NUM_DATA_PNTS], gy[NUM_DATA_PNTS], gz[NUM_DATA_PNTS], temp[NUM_DATA_PNTS];
    
    //sprintf(m_out,"MPU-6050 WHO_AM_I: %X\r\n",whoami());
    //WriteUART1(m_out);
    char who = whoami(); // ask if the imu is there
    if (who != 0x68){
        // if the imu is not there, get stuck here forever
        while(1){
            LATAbits.LATA4 = 1;
        }
    }
    
    char IMU_buf[IMU_ARRAY_LEN]; // raw 8 bit array for imu data

    while (1) {
        blink();
        
        ReadUART1(m_in,100); // wait for a newline
        // don't actually have to use what is in m
        
        // collect data
        for (i=0; i<NUM_DATA_PNTS; i++){
            _CP0_SET_COUNT(0);
            // read IMU
            burst_read_mpu6050(IMU_buf);
            ax[i] = conv_xXL(IMU_buf);
            ay[i] = conv_yXL(IMU_buf);
            az[i] = conv_zXL(IMU_buf);
            gx[i] = conv_xG(IMU_buf);
            gy[i] = conv_yG(IMU_buf);
            gz[i] = conv_zG(IMU_buf);
            temp[i] = conv_temp(IMU_buf);
            
            while(_CP0_GET_COUNT()<24000000/2/100){}
        }
        
        // print data
        for (i=0; i<NUM_DATA_PNTS; i++){
            sprintf(m_out,"%d %f %f %f %f %f %f %f\r\n",NUM_DATA_PNTS-i,ax[i],ay[i],az[i],gx[i],gy[i],gz[i],temp[i]);
            WriteUART1(m_out);
        }
        
    }
}

void blink(){
    LATAbits.LATA4 = 1;
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<24000000/2/20){}
    LATAbits.LATA4 = 0;
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT()<24000000/2/20){}
}
