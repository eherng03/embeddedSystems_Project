-- phpMyAdmin SQL Dump
-- version 4.6.6deb4
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost:3306
-- Tiempo de generación: 18-12-2017 a las 11:44:30
-- Versión del servidor: 10.1.23-MariaDB-9+deb9u1
-- Versión de PHP: 7.0.19-1

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

--
-- Volcado de datos para la tabla `humidity`
--

INSERT INTO `humidity` (`place`, `value`, `date`) VALUES
('kitchen', 19, '2017-12-04 14:23:35'),
('kitchen', 19, '2017-12-04 14:24:07'),
('kitchen', 19, '2017-12-04 14:28:54'),
('kitchen', 25, '2017-12-11 12:07:29'),
('kitchen', 26, '2017-12-11 12:08:01'),
('kitchen', 32, '2017-12-11 12:08:34'),
('kitchen', 32, '2017-12-11 12:09:08'),
('kitchen', 32, '2017-12-11 12:09:40');

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
-- Estructura de tabla para la tabla `presence`
--

CREATE TABLE `presence` (
  `place` varchar(15) CHARACTER SET latin1 NOT NULL,
  `status` bit(1) NOT NULL,
  `date` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `presence`
--

INSERT INTO `presence` (`place`, `status`, `date`) VALUES
('garage', b'1', '2017-12-18 11:30:50');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `smoke`
--

CREATE TABLE `smoke` (
  `place` varchar(15) NOT NULL,
  `status` bit(1) NOT NULL,
  `date` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `smoke`
--

INSERT INTO `smoke` (`place`, `status`, `date`) VALUES
('garage', b'0', '2017-12-18 11:18:42');

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
-- Volcado de datos para la tabla `temperature`
--

INSERT INTO `temperature` (`place`, `date`, `value`) VALUES
('kitchen', '2017-12-04 14:20:15', 24),
('kitchen', '2017-12-04 14:20:47', 24),
('kitchen', '2017-12-04 14:23:35', 23),
('kitchen', '2017-12-04 14:24:07', 24),
('kitchen', '2017-12-04 14:28:54', 24),
('kitchen', '2017-12-11 12:07:29', 18),
('kitchen', '2017-12-11 12:08:01', 18),
('kitchen', '2017-12-11 12:08:32', 18),
('kitchen', '2017-12-11 12:09:07', 18),
('kitchen', '2017-12-11 12:09:39', 18);

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
-- Indices de la tabla `presence`
--
ALTER TABLE `presence`
  ADD PRIMARY KEY (`place`),
  ADD KEY `place` (`place`),
  ADD KEY `place_2` (`place`);

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
-- Filtros para la tabla `presence`
--
ALTER TABLE `presence`
  ADD CONSTRAINT `presence_ibfk_1` FOREIGN KEY (`place`) REFERENCES `place` (`name`) ON DELETE CASCADE ON UPDATE CASCADE;

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
