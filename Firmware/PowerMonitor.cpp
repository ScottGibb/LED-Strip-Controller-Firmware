/**
 * @file PowerMonitor.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

typedef struct {
    float power;
    float current;
    float voltage;
}Power_t;
class PowerMonitor{
    public:
        PowerMonitor();
        ~PowerMonitor();

    private:
        void loop();
        float getCurrent();
        float getVoltage();
        float getPower();
        Power_t getStats();
};