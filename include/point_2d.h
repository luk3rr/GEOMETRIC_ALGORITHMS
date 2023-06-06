/*
* Filename: point_2d.h
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef POINT_2D_H_
#define POINT_2D_H_

namespace geom {
    class Point2D {
        private:
            int m_x, m_y;

        public:
            /**
            @brief Construtor padrão da classe
            */
            Point2D();

            /**
            @brief Overload do construtor da classe
            @param x, y Coordenadas do ponto
            */
            Point2D(int x, int y);

            /**
            @brief Overload do operador ==
            @param point Ponto que será usado na comparação
            @return True se as coordenadas dos dois pontos forem iguais uma a uma, False caso contrário
            */
            bool operator==(const Point2D &point) const;

            /**
            @brief Define um novo valor para a coordenada X
            @param x Novo valor da coordenada X
            */
            void SetX(int x);

            /**
            @brief Define um novo valor para a coordenada Y
            @param y Novo valor da coordenada Y
            */
            void SetY(int y);

            /**
            @brief Pega o valor da coordenada X
            @return Valor da coordenada X
            */
            int GetX();

            /**
            @brief Pega o valor da coordenada Y
            @return Valor da coordenada Y
            */
            int GetY();
    };
}

#endif // POINT_2D_H_
