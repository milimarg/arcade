/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Keys
*/

#ifndef KEYS_HPP_
    #define KEYS_HPP_

namespace arcade
{
    enum class Key {
        A_KEY,
        B_KEY,
        C_KEY,
        D_KEY,
        E_KEY,
        F_KEY,
        G_KEY,
        H_KEY,
        I_KEY,
        J_KEY,
        K_KEY,
        L_KEY,
        M_KEY,
        N_KEY,
        O_KEY,
        P_KEY,
        Q_KEY,
        R_KEY,
        S_KEY,
        T_KEY,
        U_KEY,
        V_KEY,
        W_KEY,
        X_KEY,
        Y_KEY,
        Z_KEY,
        UP_ARROW,
        LEFT_ARROW,
        DOWN_ARROW,
        RIGHT_ARROW,
        SPACE,
        ENTER,
        DELETE,
        MOUSE_BUTTON_LEFT,
        MOUSE_BUTTON_RIGHT,
        NONE,
        KEY_LIST_END,
    };

    enum class ChangeKey {
        PREV_GRAPHICAL_LIB,
        NEXT_GRAPHICAL_LIB,
        PREV_GAME_LIB,
        NEXT_GAME_LIB,
        MAIN_MENU,
        ESCAPE,
        NONE,
        CHANGE_LIST_END,
    };
}

#endif /* !KEYS_HPP_ */
