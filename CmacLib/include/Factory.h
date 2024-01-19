#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include <string>
#include "ICmac.h"

class Factory {
public:
	/// <summary>
	/// Create an untrained Cmac.
	/// </summary>
	/// <param name="numQ"></param>
	/// <param name="numLayers"></param>
	/// <param name="maxHash"></param>
	/// <param name="upper"></param>
	/// <param name="lower"></param>
	/// <param name="beta"></param>
	/// <param name="nu"></param>
	/// <returns></returns>
	std::unique_ptr<ICmac> CreateCmac(unsigned int numQ
		, unsigned int numLayers
		, unsigned int maxmem
		, unsigned int numOut
		, std::vector<double> upper
		, std::vector<double> lower
		, double beta
		, double nu);

	/// <summary>
	/// Load a Cmac from file which could include trained weights.
	/// </summary>
	/// <param name="pathfile"></param>
	/// <returns></returns>
	//std::unique_ptr<ICmac> CreateCmacFromFile(std::string pathfile);
};

#endif