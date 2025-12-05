#pragma once
#include <DIS7/EntityStatePdu.h>
#include <DIS7/ElectromagneticEmissionsPdu.h>
#include <DIS7/IFFPdu.h>
#include <DIS7/EntityStateUpdatePdu.h>
#include <DIS7/FirePdu.h>
#include <DIS7/RemoveEntityPdu.h>
#include <DIS7/DetonationPdu.h>
#include <DIS7/AttributeRecord.h>
#include <DISUtils/FactoryRemoteEntity.h>
#include <unordered_map>
#include <DISUtils/DISConfigurationsHandler.h>
#include <mutex>
#include <shared_mutex>
#include <DIS7\msLibMacro.h>

using AdditionCallback = std::function<void(const CRemoteEntity&)>;
using RemovalCallback = std::function<void(const EntityID&, bool)>;

	namespace std {
		template <>
		struct hash<EntityID>
		{
			size_t operator() (const EntityID& eID) const
			{
				long long	key = ((long long)eID.getSite() << 32) | ((long long)eID.getApplication() << 16) | ((long long)eID.getEntity());
				return hash<long long>()(key);
			}
		};
	}

	namespace std {
		template <>
		struct hash<RemoteEntityType>
		{
			size_t operator() (const RemoteEntityType& key) const noexcept
			{
				return static_cast<size_t>(key);
			}
		};
	}

	namespace DIS
	{
		class EXPORT_MACRO CRemoteEntitiesManager
		{
		private:
			static CRemoteEntitiesManager* _instance;

			std::mutex _mutexRemoteEntities;

			int	_numberofPdus{};
			double _drLagTime{};

			std::unordered_map <EntityID, CRemoteEntity*> _uMapRemoteEntities;

			std::vector<RemoteEntityType> m_enabledRemoteEntityTypes;
			std::list<FirePdu>	_firePDUsList;

			AdditionCallback  _addedCallbackFunction{nullptr};
			RemovalCallback  _removedCallbackFunction{ nullptr };

			void TriggerNewRemoteEntityAdditionCallback(const CRemoteEntity& remoteEntityObj);
			void TriggerRemoteEntityRemovalCallback(const EntityID& entityID, bool isTimedOut);

			void AddNewEntity(const EntityStatePdu& esPdu);

			void CompensateLag(EntityStatePdu& es, double lagInSeconds);

			bool IsEntityInProximityRadius(Vector3Double location1, Vector3Double location2, int radius);

			CRemoteEntitiesManager(void);
			~CRemoteEntitiesManager(void);

		public:
		
			static CRemoteEntitiesManager* GetInstance();

			bool FillFirePDUParameters(EntityID munitionExpendableID, FirePdu& firePDU);

			void Update(float deltaTime, float totalAppTime);

			//bool ComparePDUs(Pdu currentPdu, Pdu prevPdu);
			void HandleEntityStatePDU(const EntityStatePdu& esPdu);
			void HandleEntityStateUpdatePDU(const EntityStateUpdatePdu& esUpdatePdu);
			void HandleFirePdu(const FirePdu& firePdu);
			void HandleRemoveEntityPDU(const RemoveEntityPdu& rEPdu);
			void HandleDetonationPDU(const DetonationPdu& detonationPdu);
			void HandleElectromagneticEmissionPDU(const ElectromagneticEmissionsPdu& eePdu);
			void HandleIffPDU(const IFFPdu& iffPdu);
			void HandleAttributePDU(const AttributePdu& atrPdu);

			///     <summary> * Get Remote Entity by EntityID
			///     * <p>
			///     * Returns Remote Entity w.r.t. Entity ID
			///		* Don't update return value</summary>
			CRemoteEntity* GetRemoteEntityByEntityID(EntityID entityID)const;

			///     <summary> * Get Remote Entity by EntityID and Force ID
			///     * <p>
			///     * Returns Remote Entity w.r.t. Entity ID and Force ID
			///		* This function will skip data containing parameter Force ID
			///		* Don't update return value</summary>

			CRemoteEntity* GetRemoteEntityByEntityIDAndForceID(EntityID entityID, int omittedforceID)const;

			const std::unordered_map <EntityID, CRemoteEntity*>& GetRemoteEntities()const;
			
			bool CompareEntityIDs(EntityID e1, EntityID e2);

			void EnableRemoteEntities(std::initializer_list<RemoteEntityType> remoteEntityTypes);

			bool IsEntityTypeEnabled(RemoteEntityType type);

			void AddEntityAddtionCallback(AdditionCallback callbackFunction);
			void AddEntityAddtionCallback(void(*cb)(const CRemoteEntity&));
			void RemoveEntityAddtionCallback();
			
			void AddEntityRemovalCallback(RemovalCallback callbackFunction);
			void AddEntityRemovalCallback(void(*cb)(const EntityID&, bool));
			void RemoveEntityRemovalCallback();

			void ClearList();
			};
	}
