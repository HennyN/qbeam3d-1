/***************************************************************************
                          scanner.h  -  description
                             -------------------
    begin                : Die M�r 18 2003
    copyright            : (C) 2003 by Maximilian Hrabowski
    email                : maximilian@hrabowski.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SCANNER_H
#define SCANNER_H


/** Abstrakte Basisklasse f�r einen Scanner

    Die Schnittstelle ist m�glichst einfach und kompakt gehalten.

  *@author Maximilian Hrabowski
  */

#include <string>
#include "Mesh.h"
#include "Plane2DMediator.h"

class Scanner
{
public:

		class Capabilities
		{
		public:
			Capabilities(): _cornerLLN(), _cornerURF(), _resolutions()
			{}
		
			const Mesh::Point& cornerLLN() const { return _cornerLLN; }
			const Mesh::Point& cornerURF() const { return _cornerURF; }
			unsigned long resolution( unsigned dir ) const { return _resolutions.at(dir); }

			void setResolution( unsigned long res, int dir=-1 )
			{
				if( dir<0 )
					_resolutions.push_back(res);
				else if( unsigned(dir)<_resolutions.size())
					_resolutions[unsigned(dir)]=res;
			}
			void setBoundingCube( const Mesh::Point &lln, const Mesh::Point& urf )
			{
				_cornerLLN=lln;
				_cornerURF = urf;
			}
			
		private:
			//! Kubus der das gr��tm�gliche Scanobject enth�lt
			Mesh::Point _cornerLLN; // Lower Left Near
			Mesh::Point _cornerURF; // Upper Right Far
			/** maximale Anzahl von Schritten f�r jede Bewegungsrichtung in denen gescannt wird
			* Anzahl der Eintr�ge entspricht Anzahl von Scanrichtungen
			*/
			std::vector<unsigned long> _resolutions;
		};

	typedef enum {  UNKNOWN=0,			// intitial state
					INITIALIZED,		// init() success,
					CALIBRATED,			// init() success && calibrate() success
					READY_WAITING,		// init() && open() success
					SCANNING,			// during command execution
					ERROR				// error occured
				} ScannerState;

	Scanner() : m_plotView(0) {}
	virtual ~Scanner() {};

	void setPlotView( Plane2DMediator* p=0 ) { m_plotView = p; }

// Beschreibung

  /** name des scanners */
	virtual const std::string& name() const =0;
  /** beschreibung */
	virtual const std::string& description() const =0;
  /** liste von Modi, in denen der Scanner betrieben werden kann
      z.B. verschiedenen Geschwindigkeiten und Qualit�tsstufen.
      first -> Bezeichnung
      second -> n�here Beschreibung ( auch mehrzeilig )
  */
	virtual const std::vector<std::pair<std::string,std::string> >& modes() const = 0;

// Parameter des Scanners abfragen

	/** Gibt Beschreibung der F�higkeiten des Scanners zur�ck */
	virtual const Capabilities& capabilities() const =0;

	// zum scannen

	/** Der Scanner wird initialisiert. Gibt true zur�ck wenn der Scanner einsatzbereit ist */
	virtual bool init()  = 0;
	/** calibiriert des Scanners, true wenn erfolgreich */
	virtual bool calibrate() = 0;
	/** gibt true zur�ck wenn der scanner bereit ist */
	virtual bool ready() const=0;

	/** Startet den scanvorgang */
	virtual bool start() = 0;
	/** Stoppt den scanvorgang */
	virtual bool stop() = 0;

	/** drive back to zero, reposition reader on axis */
	virtual bool recalcPosition( unsigned axis, unsigned pos )=0;
	/** move "reader" to point, absolut */
	virtual bool moveTo( unsigned axis, unsigned pos )=0;
	/** increment */
	virtual bool moveNext( unsigned axis )=0;
	/** decrement */
	virtual bool movePrevious( unsigned axis )=0;
	/** get point at current pos */
	virtual bool getPoint( Mesh::Point& p )=0;

protected:

	Plane2DMediator* m_plotView;

};

#endif



