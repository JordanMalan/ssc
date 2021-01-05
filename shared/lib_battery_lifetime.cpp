#include "lib_battery_lifetime.h"
#include "lib_battery_lifetime_calendar_cycle.h"
#include "lib_battery_lifetime_nmc.h"

lifetime_params::lifetime_params() {
    cal_cyc = std::make_shared<calendar_cycle_params>();
}

lifetime_state::lifetime_state(){
    cycle = std::make_shared<cycle_state>();
    calendar = std::make_shared<calendar_state>();
}

lifetime_state::lifetime_state(const std::shared_ptr<cycle_state>& cyc, const std::shared_ptr<calendar_state>& cal) {
    cycle = cyc;
    calendar = cal;
    q_relative = fmin(cycle->q_relative_cycle, calendar->q_relative_calendar);
}

lifetime_state &lifetime_state::operator=(const lifetime_state &rhs) {
    if (this != &rhs) {
        q_relative = rhs.q_relative;
        n_cycles = rhs.n_cycles;
        range = rhs.range;
        average_range = rhs.average_range;
        day_age_of_battery = rhs.day_age_of_battery;
        *cycle = *rhs.cycle;
        *calendar = *rhs.calendar;
    }
    return *this;
}

lifetime_t::lifetime_t(const lifetime_t &rhs) {
    state = std::make_shared<lifetime_state>(*rhs.state);
    params = std::make_shared<lifetime_params>(*rhs.params);
}

lifetime_t &lifetime_t::operator=(const lifetime_t &rhs) {
    if (this != &rhs) {
        *params = *rhs.params;
        *state = *rhs.state;
    }
    return *this;
}

double lifetime_t::capacity_percent() { return state->q_relative; }


lifetime_params lifetime_t::get_params() { return *params; }

lifetime_state lifetime_t::get_state() {
    lifetime_state state_copy = *state;
    return state_copy;
}
