-- phpMyAdmin SQL Dump
-- version 4.6.5.2
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 04-12-2017 a las 10:38:51
-- Versión del servidor: 10.1.21-MariaDB
-- Versión de PHP: 5.6.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `empotrados`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `humidity`
--

CREATE TABLE `humidity` (
  `place` varchar(15) NOT NULL,
  `value` float NOT NULL,
  `date` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `light`
--

CREATE TABLE `light` (
  `ID` int(5) NOT NULL,
  `place` varchar(15) NOT NULL,
  `state` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Volcado de datos para la tabla `light`
--

INSERT INTO `light` (`ID`, `place`, `state`) VALUES
(1, 'bathroom', 0),
(1, 'garage', 0),
(1, 'kitchen', 0),
(1, 'room', 1),
(2, 'bathroom', 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `place`
--

CREATE TABLE `place` (
  `name` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `place`
--

INSERT INTO `place` (`name`) VALUES
('bathroom'),
('garage'),
('kitchen'),
('room');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `smoke`
--

CREATE TABLE `smoke` (
  `place` varchar(15) NOT NULL,
  `status` bit(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `temperature`
--

CREATE TABLE `temperature` (
  `place` varchar(15) NOT NULL,
  `date` datetime NOT NULL,
  `value` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `humidity`
--
ALTER TABLE `humidity`
  ADD PRIMARY KEY (`place`,`date`);

--
-- Indices de la tabla `light`
--
ALTER TABLE `light`
  ADD PRIMARY KEY (`ID`,`place`),
  ADD KEY `place` (`place`);

--
-- Indices de la tabla `place`
--
ALTER TABLE `place`
  ADD PRIMARY KEY (`name`);

--
-- Indices de la tabla `smoke`
--
ALTER TABLE `smoke`
  ADD PRIMARY KEY (`place`),
  ADD KEY `place` (`place`);

--
-- Indices de la tabla `temperature`
--
ALTER TABLE `temperature`
  ADD PRIMARY KEY (`place`,`date`);

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `humidity`
--
ALTER TABLE `humidity`
  ADD CONSTRAINT `humidity_ibfk_1` FOREIGN KEY (`place`) REFERENCES `place` (`name`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Filtros para la tabla `light`
--
ALTER TABLE `light`
  ADD CONSTRAINT `light_ibfk_1` FOREIGN KEY (`place`) REFERENCES `place` (`name`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Filtros para la tabla `smoke`
--
ALTER TABLE `smoke`
  ADD CONSTRAINT `smoke_ibfk_1` FOREIGN KEY (`place`) REFERENCES `place` (`name`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Filtros para la tabla `temperature`
--
ALTER TABLE `temperature`
  ADD CONSTRAINT `temperature_ibfk_1` FOREIGN KEY (`place`) REFERENCES `place` (`name`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
