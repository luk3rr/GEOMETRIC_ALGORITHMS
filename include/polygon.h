/*
* Filename: polygon.h
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef POLYGON_H_
#define POLYGON_H_

#include "list_doubly_linked.h"
#include "point_2d.h"

namespace geom {
    class Polygon {
        private:
            dlkd::List<Point2D> m_points;

        public:
            /**
            @brief Construtor padrão da classe
            */
            Polygon();

            /**
            @brief Overload do construtor da classe
            @param points Lista de pontos que definem o polígono
            */
            Polygon(dlkd::List<Point2D> points);

            /**
            @brief Pega a quantidade de pontos que formam o polígono
            @return Inteiro que representa a quantidade de pontos que definem o polígono
            */
            int GetNumPoints();

            /**
            @brief Insere um ponto no conjunto de pontos que formam o polígono
            @param point Ponto que será inserido no conjunto
            */
            void InsertPoint(Point2D point);

            /**
            @brief Insere um ponto no conjunto de pontos que formam o polígono
            @param x, y Coordenadas do novo ponto
            */
            void InsertPoint(int x, int y);

            /**
            @brief Deleta um ponto do conjunto de pontos que formam o polígono
            @param point Ponto que será deletado do conjunto
            @throw ?
            */
            void DeletePoint(Point2D point);

            /**
            @brief Deleta um ponto do conjunto de pontos que formam o polígono
            @param x, y Coordenadas do ponto que será removido
            */
            void DeletePoint(int x, int y);

            /**
            @brief Remove todos os pontos que formam o polígono
            */
            void Delete();

            /**
            @brief Verifica se o ponto dado faz parte do conjunto de pontos que definem o polígono
            @param point Ponto que será utilizado na verificação
            @return True se o ponto está no conjunto de pontos que definem o polígono, False caso contrário
            */
            bool IsPointOnPolygon(Point2D point);

            /**
            @brief Verifica se o ponto dado faz parte do conjunto de pontos que definem o polígono
            @param x,y Coordenadas do ponto que será utilizado na verificação
            @return True se o ponto está no conjunto de pontos que definem o polígono, False caso contrário
            */
            bool IsPointOnPolygon(int x, int y);
    };
}

#endif // POLYGON_H_
